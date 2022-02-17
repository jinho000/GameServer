#include "pch.h"
#include "TCPListener.h"
#include "SocketAddress.h"
#include "ServerHelper.h"
#include "AcceptExOverlapped.h"
#include "TCPSession.h"
#include "GameServerBase/ServerDebug.h"

TCPListener::TCPListener(const IPEndPoint& _EndPoint, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback)
	: m_listenerSocket(NULL)
	, m_ipEndPoint(_EndPoint)
	, m_pJobQueue(ServerQueue::WORK_TYPE::Default, 4)
	, m_acceptCallback(_acceptCallback)
{
	Initialize(_EndPoint);
}

TCPListener::TCPListener(const std::string& _ip, int _port, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback)
	: TCPListener(IPEndPoint(_ip, _port), _acceptCallback)
{
}


void TCPListener::Initialize(const IPEndPoint& _EndPoint)
{
	// 소켓 라이브러리 초기화
	ServerHelper::InitSocketLib();

	m_listenerSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_listenerSocket)
	{
		ServerDebug::LogError("WSASocket error");
		return;
	}


	// IP4, IP6 구분?
	SocketAddress addrSerial = (_EndPoint.Serialize());
	int ErrorCode = ::bind(m_listenerSocket, reinterpret_cast<const sockaddr*>(addrSerial.GetBuffer()), (int)addrSerial.GetBufferLength());
	if (SOCKET_ERROR == ErrorCode)
	{
		CloseSocket();
		ServerDebug::LogError("bind error");
		return;
	}

	BOOL on = TRUE;
	ErrorCode = setsockopt(m_listenerSocket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, reinterpret_cast<const char*>(&on), sizeof(on));
	if (SOCKET_ERROR == ErrorCode)
	{
		CloseSocket();
		ServerDebug::LogError("socket opt error");
		return;
	}

	int backLog = 512;
	ErrorCode = listen(m_listenerSocket, backLog);
	if (SOCKET_ERROR == ErrorCode)
	{
		CloseSocket();
		ServerDebug::LogError("listen error");
		return;
	}

	// Bind queue
	// 리스너 소켓과 접속을 받아들이는 함수 연결
	// 비동기 처리
	m_pJobQueue.NetworkAyncBind(m_listenerSocket, std::bind(&TCPListener::OnAccept, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	// Start Accept
	StartAccept(10);
}

void TCPListener::StartAccept(UINT _backLog)
{
	if (128 < _backLog)
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		_backLog = sysInfo.dwNumberOfProcessors;
	}

	// backlog 개수만큼 미리 소켓을 만들어 놓음
	for (UINT i = 0; i < _backLog; i++)
	{
		AsyncAccept();
	}
}

void TCPListener::AsyncAccept()
{
	PtrSTCPSession newSession = nullptr;
	{
		m_connectPoolLock.lock();

		if (m_connectionPool.empty())
		{
			newSession = std::make_shared<TCPSession>();
			newSession->Initialize();
			newSession->SetParent(this);
		}
		else
		{
			// 커넥션 풀에 세션이 있을경우 재활용
			newSession = m_connectionPool.front();
			m_connectionPool.pop_front();
			newSession->SetReuse();
		}

		m_connectPoolLock.unlock();
	}

	// 접속 완료 후 전달할 overlapped
	std::unique_ptr<AcceptExOverlapped> acceptExOver = std::make_unique<AcceptExOverlapped>(newSession);

	// AcceptEx 함수 호출
	DWORD dwByte = 0;
	BOOL result = AcceptEx(m_listenerSocket
		, newSession->GetSessionSocket()
		, acceptExOver->GetBuffer()
		, 0
		, sizeof(sockaddr_in) + 16
		, sizeof(sockaddr_in) + 16
		, &dwByte
		, acceptExOver->GetLPOverlapped());

	if (FALSE == result)
	{
		if (ERROR_IO_PENDING != WSAGetLastError())
		{
			ServerDebug::LogInfo("AcceptEx Error");
			return;
		}
	}

	// unique 포인터 소유권 포기
	acceptExOver.release();
}

void TCPListener::OnAccept(BOOL _result, DWORD _byteSize, LPOVERLAPPED _overlapped)
{
	// 접속자가 들어와 세션이 생긴경우
	// 대기소켓을 하나더 생성
	AsyncAccept();

	if (nullptr == _overlapped)
	{
		ServerDebug::LogWarning("OnAccept overlapped가 없음");
		return;
	}

	if (nullptr == m_acceptCallback)
	{
		ServerDebug::LogWarning("accept callback이 없음");
		return;
	}

	if (0 == _result)
	{
		ServerDebug::LogError("accept error");
		return;
	}

	// overlapped 객체 가져오기
	std::unique_ptr<AcceptExOverlapped> acceptExOver = std::unique_ptr<AcceptExOverlapped>(reinterpret_cast<AcceptExOverlapped*>(reinterpret_cast<char*>(_overlapped) - sizeof(void*)));
	
	// acceptExOver 객체에 리모트, 로컬 주소값을 채워넣음
	acceptExOver->Excute(_result, _byteSize);

	// 클라와 연결된 세션에 IOCP 연결후 리시브 요청
	PtrSTCPSession session = acceptExOver->GetTCPSession();
	session->BindQueue(m_pJobQueue);
	session->RequestRecv();
	
	// 세션 저장하기
	m_connecsLock.lock();
	m_connections.insert(std::make_pair(session->GetSessionID(), session));
	m_connecsLock.unlock();

	// callback 함수 실행
	m_acceptCallback(acceptExOver->GetTCPSession());
}

void TCPListener::CloseSession(PtrSTCPSession _tcpSession)
{
	// session에서 처리가 끝남

	// 관리 맵에서 삭제
	{
		std::lock_guard<std::mutex> lock(m_connecsLock);
		m_connections.erase(_tcpSession->GetSessionID());
	}

	// 재활용하기 위해 connection 풀에 추가
	{
		std::lock_guard<std::mutex> lock(m_connectPoolLock);
		m_connectionPool.push_back(_tcpSession);
	}
}

void TCPListener::CloseSocket()
{
	if (NULL != m_listenerSocket)
	{
		closesocket(m_listenerSocket);
		m_listenerSocket = NULL;
	}
}

void TCPListener::BroadCast(const std::vector<uint8_t>& _buffer, PtrSTCPSession _requestSession)
{
	ServerDebug::LogInfo("BroadCast");

	std::lock_guard<std::mutex> lockGuard(m_connecsLock);

	auto iter = m_connections.begin();
	while (iter != m_connections.end())
	{
		// 패킷요청한 세션을 무시하고 전달하는 경우
		if (iter->second == _requestSession)
		{
			continue;
		}

		iter->second->Send(_buffer);
		++iter;
	}
}

void TCPListener::BroadCast(const std::vector<uint8_t>& _buffer)
{
	BroadCast(_buffer, nullptr);
}
