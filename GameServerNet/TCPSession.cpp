#include "pch.h"
#include "TCPSession.h"
#include "GameServerBase/ServerUnique.h"

TCPSession::TCPSession()
	: m_conectId(ServerUnique::GetNextUniqueId())
	, m_sessionSocket(NULL)
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


}

TCPSession::~TCPSession()
{
}

void TCPSession::CloseSocket()
{
	if (NULL != m_sessionSocket)
	{
		closesocket(m_sessionSocket);
		m_sessionSocket = NULL;
	}
}

SOCKET TCPSession::GetSessionSocket() const
{
	return m_sessionSocket;
}

__int64 TCPSession::GetSessionID() const
{
	return m_conectId;
}
