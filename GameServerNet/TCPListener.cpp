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
	// ���� ���̺귯�� �ʱ�ȭ
	ServerHelper::InitSocketLib();

	m_listenerSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_listenerSocket)
	{
		ServerDebug::LogError("WSASocket error");
		return;
	}


	// IP4, IP6 ����?
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
	// ������ ���ϰ� ������ �޾Ƶ��̴� �Լ� ����
	// �񵿱� ó��
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

	// backlog ������ŭ �̸� ������ ����� ����
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
			// Ŀ�ؼ� Ǯ�� ������ ������� ��Ȱ��
			newSession = m_connectionPool.front();
			m_connectionPool.pop_front();
			newSession->SetReuse();
		}

		m_connectPoolLock.unlock();
	}

	// ���� �Ϸ� �� ������ overlapped
	std::unique_ptr<AcceptExOverlapped> acceptExOver = std::make_unique<AcceptExOverlapped>(newSession);

	// AcceptEx �Լ� ȣ��
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

	// unique ������ ������ ����
	acceptExOver.release();
}

void TCPListener::OnAccept(BOOL _result, DWORD _byteSize, LPOVERLAPPED _overlapped)
{
	// �����ڰ� ���� ������ ������
	// �������� �ϳ��� ����
	AsyncAccept();

	if (nullptr == _overlapped)
	{
		ServerDebug::LogWarning("OnAccept overlapped�� ����");
		return;
	}

	if (nullptr == m_acceptCallback)
	{
		ServerDebug::LogWarning("accept callback�� ����");
		return;
	}

	if (0 == _result)
	{
		ServerDebug::LogError("accept error");
		return;
	}

	// overlapped ��ü ��������
	std::unique_ptr<AcceptExOverlapped> acceptExOver = std::unique_ptr<AcceptExOverlapped>(reinterpret_cast<AcceptExOverlapped*>(reinterpret_cast<char*>(_overlapped) - sizeof(void*)));
	
	// acceptExOver ��ü�� ����Ʈ, ���� �ּҰ��� ä������
	acceptExOver->Excute(_result, _byteSize);

	// Ŭ��� ����� ���ǿ� IOCP ������ ���ú� ��û
	PtrSTCPSession session = acceptExOver->GetTCPSession();
	session->BindQueue(m_pJobQueue);
	session->RequestRecv();
	
	// ���� �����ϱ�
	m_connecsLock.lock();
	m_connections.insert(std::make_pair(session->GetSessionID(), session));
	m_connecsLock.unlock();

	// callback �Լ� ����
	m_acceptCallback(acceptExOver->GetTCPSession());
}

void TCPListener::CloseSession(PtrSTCPSession _tcpSession)
{
	// session���� ó���� ����

	// ���� �ʿ��� ����
	{
		std::lock_guard<std::mutex> lock(m_connecsLock);
		m_connections.erase(_tcpSession->GetSessionID());
	}

	// ��Ȱ���ϱ� ���� connection Ǯ�� �߰�
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
		// ��Ŷ��û�� ������ �����ϰ� �����ϴ� ���
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
