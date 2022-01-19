#include "pch.h"
#include "TCPSession.h"
#include "GameServerBase/ServerUnique.h"
#include "Overlapped.h"
#include "RecvOverlapped.h"

TCPSession::TCPSession()
	: m_conectId(ServerUnique::GetNextUniqueId())
	, m_sessionSocket(NULL)
	, m_recvOverlapped(nullptr)
	, m_recvCallBack(nullptr)
	, m_callClose(false)
{
}

TCPSession::~TCPSession()
{
	if (nullptr != m_recvOverlapped)
	{
		delete m_recvOverlapped;
		m_recvOverlapped = nullptr;
	}
}

void TCPSession::OnCallback(PtrWTCPSession _weakSession, BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped)
{
	if (nullptr == _lpOverlapped)
	{
		return;
	}

	// 오버렙드 주소에서 오버렙드를 가진 객체 가져오기
	Overlapped* pOverlapped = reinterpret_cast<Overlapped*>(reinterpret_cast<char*>(_lpOverlapped) - sizeof(void*));
	pOverlapped->Excute(_result, _numberOfBytes);
}

void TCPSession::CloseSocket()
{
	if (NULL != m_sessionSocket)
	{
		closesocket(m_sessionSocket);
		m_sessionSocket = NULL;
	}
}

bool TCPSession::BindQueue(const ServerQueue& _jobQueue)
{
	PtrWTCPSession ptrThis = std::dynamic_pointer_cast<TCPSession>(shared_from_this());
	return _jobQueue.NetworkAyncBind(m_sessionSocket, std::bind(&TCPSession::OnCallback, ptrThis, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void TCPSession::RequestRecv()
{
	DWORD recvByte = 0;
	DWORD dwFlags  = 0;

	// 리시브 요청을 할 때마다 오버렙드 클리어
	m_recvOverlapped->Clear();

	if (SOCKET_ERROR == WSARecv(
		m_sessionSocket
		, m_recvOverlapped->GetWSABuffer()
		, 1
		, &recvByte
		, &dwFlags
		, m_recvOverlapped->GetLPOverlapped()
		, nullptr))
	{
		int Error = WSAGetLastError();
		if (WSA_IO_PENDING != Error)
		{
			ServerDebug::GetLastErrorPrint();
			return;
		}
	}

}

void TCPSession::OnRecv(const char* _data, DWORD _byteSize)
{
	std::vector<char> outBuffer = std::vector<char>(_byteSize);
	memcpy_s(&outBuffer[0], _byteSize, _data, _byteSize);
	// 프로토콜 처리
	///////////////


	// 리시브 콜백 처리
	if (nullptr != m_recvCallBack)
	{
		m_recvCallBack(std::dynamic_pointer_cast<TCPSession>(shared_from_this()), outBuffer);
	}
	
	if (false == m_callClose)
	{
		// 리시브 처리 후 다시 리시브 요청
		RequestRecv();
	}
}

SOCKET TCPSession::GetSessionSocket() const
{
	return m_sessionSocket;
}

void TCPSession::Initialize()
{
	m_sessionSocket = WSASocket(AF_INET
		, SOCK_STREAM
		, IPPROTO::IPPROTO_TCP
		, NULL
		, NULL
		, WSA_FLAG_OVERLAPPED
	);

	if (INVALID_SOCKET == m_sessionSocket)
	{
		ServerDebug::GetLastErrorPrint();
		return;
	}

	int errorCode = 0;

	// 옵션설정

	// 네이글 알고리즘 끄기
	{
		BOOL bNoDelay = TRUE;
		errorCode = setsockopt(m_sessionSocket
			, IPPROTO_TCP
			, TCP_NODELAY
			, reinterpret_cast<const char*>(&bNoDelay)
			, sizeof(BOOL)
		);

		if (SOCKET_ERROR == errorCode)
		{
			ServerDebug::GetLastErrorPrint();
			CloseSocket();
			return;
		}
	}

	// 소켓 재활용 옵션
	{
		BOOL bReuse = TRUE;
		errorCode = setsockopt(m_sessionSocket
			, SOL_SOCKET
			, SO_REUSEADDR
			, reinterpret_cast<const char*>(&bReuse)
			, sizeof(BOOL)
		);

		if (SOCKET_ERROR == errorCode)
		{
			ServerDebug::GetLastErrorPrint();
			CloseSocket();
			return;
		}
	}

	// 연결관련 옵션
	{
		LINGER lin;
		lin.l_linger = 0;
		lin.l_onoff = 1;

		BOOL bReuse = TRUE;
		errorCode = setsockopt(m_sessionSocket
			, SOL_SOCKET
			, SO_LINGER
			, reinterpret_cast<const char*>(&lin)
			, sizeof(LINGER)
		);

		if (SOCKET_ERROR == errorCode)
		{
			ServerDebug::GetLastErrorPrint();
			CloseSocket();
			return;
		}
	}

	m_recvOverlapped = new RecvOverlapped(std::dynamic_pointer_cast<TCPSession>(shared_from_this()));
}

__int64 TCPSession::GetSessionID() const
{
	return m_conectId;
}

void TCPSession::SetCallBack(RecvCallBack _recvCallBack)
{
	if (nullptr == _recvCallBack)
	{
		ServerDebug::LogError("receive callback is nullptr");
		return;
	}

	m_recvCallBack = _recvCallBack;
}
