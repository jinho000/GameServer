#include "pch.h"
#include "TCPListener.h"
#include "SocketAddress.h"
#include "ServerHelper.h"
#include "AcceptExOverlapped.h"
#include "TCPSession.h"
#include "GameServerBase/ServerDebug.h"

UINT TCPListener::listenThreadCount = 4;

TCPListener::TCPListener()
	: m_listenerSocket(NULL)
	, m_ipEndPoint()
	, m_pNetQueue(nullptr)
	, m_acceptCallback(nullptr)
	, m_listenCallback(std::bind(&TCPListener::OnAccept, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
{
}

TCPListener::~TCPListener()
{
}

void TCPListener::Initialize(const std::string _ip, int _port, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback)
{
	m_acceptCallback = _acceptCallback;
	m_ipEndPoint = IPEndPoint(_ip, _port);

	m_listenerSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_listenerSocket)
	{
		ServerDebug::LogError("WSASocket error");
		return;
	}


	SocketAddress addrSerial = (m_ipEndPoint.Serialize());
	int ErrorCode = ::bind(m_listenerSocket, reinterpret_cast<const sockaddr*>(addrSerial.GetBuffer()), (int)addrSerial.GetBufferLength());
	if (SOCKET_ERROR == ErrorCode)
	{
		CloseSocket();
		ServerDebug::LogError("bind error");
		ServerDebug::GetLastErrorPrint();
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
}

void TCPListener::StartAccept(UINT _backLog)
{
	if (128 < _backLog)
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		_backLog = sysInfo.dwNumberOfProcessors;
	}

	// backlog 개수만큼 미리 세션을 만들어 놓음
	for (UINT i = 0; i < _backLog; i++)
	{
		CreateAcceptSession();
	}
}

void TCPListener::BindNetQueue(const ServerQueue& _workQueue)
{
	static bool once = false;
	if (once == true)
	{
		ServerDebug::AssertDebugMsg("Bind NetQueue twice");
		return;
	}
	once = true;


	// Bind queue
	// 리스너 소켓과 접속을 받아들이는 함수 연결
	// 비동기 처리
	m_pNetQueue = &_workQueue;
	m_pNetQueue->RegistSocket(m_listenerSocket, &m_listenCallback);
}

void TCPListener::CreateAcceptSession()
{
	PtrSTCPSession newSession = nullptr;
	{
		m_acceptPoolLock.lock();

		if (m_acceptPool.empty())
		{
			newSession = std::make_shared<TCPSession>();
			newSession->Initialize();
			newSession->SetParent(this);
			m_sessionPool.push_back(newSession);
			
			std::string log = "Create ";
			log += std::to_string(static_cast<int>(newSession->GetSessionSocket()));
			log += " Socket";
			ServerDebug::LogInfo(log);
		}
		else
		{
			// 커넥션 풀에 세션이 있을경우 재활용
			newSession = m_acceptPool.front();
			m_acceptPool.pop_front();
			newSession->SetReuse();

			//std::string log = "Reuse ";
			//log += std::to_string(static_cast<int>(newSession->GetSessionSocket()));
			//log += " Socket";
			//ServerDebug::LogInfo(log);
		}

		m_acceptPoolLock.unlock();
	}

	// 접속 완료 후 전달할 overlapped
	AcceptExOverlapped* pAccetExOver = newSession->GetAcceptExOverlapped();

	// AcceptEx 함수 호출
	DWORD dwByte = 0;
	BOOL result = AcceptEx(m_listenerSocket
		, newSession->GetSessionSocket()
		, pAccetExOver->GetBuffer()
		, 0
		, sizeof(sockaddr_in) + 16
		, sizeof(sockaddr_in) + 16
		, &dwByte
		, pAccetExOver->GetLPOverlapped());

	if (FALSE == result)
	{
		if (ERROR_IO_PENDING != WSAGetLastError())
		{
			ServerDebug::LogInfo("AcceptEx Error");
			return;
		}
	}
}

void TCPListener::OnAccept(BOOL _result, DWORD _byteSize, LPOVERLAPPED _overlapped)
{
	ServerDebug::LogInfo("Client request connection");

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
	AcceptExOverlapped* acceptExOver = reinterpret_cast<AcceptExOverlapped*>(reinterpret_cast<char*>(_overlapped) - sizeof(void*));

	// acceptExOver 객체에 리모트, 로컬 주소값을 채워넣음
	acceptExOver->Excute(_result, _byteSize);

	// 클라와 연결된 세션에 IOCP 연결후 리시브 요청
	std::shared_ptr<TCPSession> session = acceptExOver->GetTCPSession();
	session->BindQueue(*m_pNetQueue);
	session->RequestRecv();

	// 세션 저장하기
	m_connectionPoolLock.lock();
	m_connectionPool.insert(std::make_pair(session->GetSessionID(), session));

	m_connectionPoolLock.unlock();

	// callback 함수 실행
	m_acceptCallback(session);


	// 접속자가 들어와 세션이 생긴경우
	// 대기소켓을 하나더 생성
	CreateAcceptSession();
}

void TCPListener::CloseSession(PtrSTCPSession _tcpSession)
{
	// session에서 처리가 끝남

	// 관리 맵에서 삭제
	{
		std::lock_guard<std::mutex> lock(m_connectionPoolLock);
		m_connectionPool.erase(_tcpSession->GetSessionID());
	}

	// 재활용하기 위해 connection 풀에 추가
	{
		std::lock_guard<std::mutex> lock(m_acceptPoolLock);
		m_acceptPool.push_back(_tcpSession);

		std::string log = "Reuse ";
		log += std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
		log += " Socket";
		ServerDebug::LogInfo(log);
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

void TCPListener::BroadCast(const std::vector<uint8_t>& _buffer, PtrSTCPSession _exceptSession)
{
	ServerDebug::LogInfo("BroadCast");

	std::lock_guard<std::mutex> lockGuard(m_connectionPoolLock);

	auto iter = m_connectionPool.begin();
	while (iter != m_connectionPool.end())
	{
		// 패킷요청한 세션을 무시하고 전달하는 경우
		if (iter->second == _exceptSession)
		{
			++iter;
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
