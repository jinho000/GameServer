#include "pch.h"
#include "TCPSession.h"
#include "GameServerBase/ServerUnique.h"
#include "Overlapped.h"
#include "RecvOverlapped.h"
#include "DisconnectOverlapped.h"
#include "SendOverlapped.h"
#include "AcceptExOverlapped.h"

TCPSession::TCPSession()
	: m_conectId(ServerUnique::GetNextUniqueId())
	, m_sessionSocket(NULL)
	, m_acceptExOverlapped(nullptr)
	, m_recvOverlapped(nullptr)
	, m_disconOverlapped(nullptr)
	, m_recvCallBack(nullptr)
	, m_closeCallBack(nullptr)
	, m_callClose(false)
	, m_bReuseSocket(false)
{
}

TCPSession::~TCPSession()
{
	if (nullptr != m_recvOverlapped)
	{
		delete m_recvOverlapped;
		m_recvOverlapped = nullptr;
	}

	if (nullptr != m_acceptExOverlapped)
	{
		delete m_acceptExOverlapped;
		m_acceptExOverlapped = nullptr;
	}

	if (nullptr != m_disconOverlapped)
	{
		delete m_disconOverlapped;
		m_disconOverlapped = nullptr;
	}

	if (nullptr != m_sendOverlapped)
	{
		delete m_sendOverlapped;
		m_sendOverlapped = nullptr;
	}
}

void TCPSession::OnCallback(BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped)
{
	if (nullptr == _lpOverlapped)
	{
		return;
	}

	// 오버렙드 주소에서 오버렙드를 가진 객체 가져오기
	Overlapped* pOverlapped = reinterpret_cast<Overlapped*>(reinterpret_cast<char*>(_lpOverlapped) - sizeof(void*));
	pOverlapped->Excute(_result, _numberOfBytes);
}

void TCPSession::CloseSession(bool _forceClose)
{
	// 세션 종료 상태 처리
	m_callClose = true;

	// close callback 실행
	if (nullptr != m_closeCallBack)
	{
		m_closeCallBack(std::dynamic_pointer_cast<TCPSession>(shared_from_this()));
	}

	if (false == _forceClose)
	{
		if (INVALID_SOCKET == m_sessionSocket)
		{
			ServerDebug::AssertDebugMsg("session socket invalid");
			return;
		}

		if (nullptr == m_disconOverlapped)
		{
			ServerDebug::AssertDebugMsg("disconOverlapped invalid");
			return;
		}

		BOOL bResult = TransmitFile(m_sessionSocket, 0, 0, 0
			, m_disconOverlapped->GetLPOverlapped()
			, 0
			, TF_DISCONNECT | TF_REUSE_SOCKET
		);

		if (FALSE == bResult)
		{
			int iError = WSAGetLastError();
			if (ERROR_IO_PENDING != iError)
			{
				ServerDebug::GetLastErrorPrint();
			}
		}
	}
	else
	{
		// 강제 종료인 경우
		CloseSocket();
	}

	// 새로운 데이터를 받기위해 Overlapped 정리
	m_acceptExOverlapped->ResetOverlapped();
}

void TCPSession::CloseSocket()
{
	if (NULL != m_sessionSocket)
	{
		shutdown(m_sessionSocket, SD_BOTH);
		closesocket(m_sessionSocket);
		m_sessionSocket = INVALID_SOCKET;
	}
}


void TCPSession::UnregisterSession()
{
	TCPListener* pListener = GetParent<TCPListener>();
	if (nullptr == pListener)
	{
		ServerDebug::AssertDebugMsg("서버와 연결되지 않는 세션이 존재");
		return;
	}
	
	pListener->CloseSession(std::dynamic_pointer_cast<TCPSession>(shared_from_this()));
	
	// 소켓 종료 후 새로운 아이디를 받음
	m_conectId = ServerUnique::GetNextUniqueId();

	m_callClose = false;
}

void TCPSession::SetReuse()
{
	m_bReuseSocket = true;
}

bool TCPSession::BindQueue(const ServerQueue& _workQueue)
{
	if (m_bReuseSocket) return true;

	return _workQueue.RegistSocket(m_sessionSocket, &m_IOCallback);
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
	ServerDebug::LogInfo("Session Recv Packet");

	std::vector<uint8_t> outBuffer = std::vector<uint8_t>(_byteSize);
	memcpy_s(&outBuffer[0], _byteSize, _data, _byteSize);
	
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

void TCPSession::Send(const std::vector<uint8_t>& _buffer)
{
	if (_buffer.empty())
	{
		return;
	}

	// Send 요청시 마다 클리어
	m_sendOverlapped->Clear();

	DWORD byteSize = 0;
	DWORD flag     = 0;
	m_sendOverlapped->CopyFrom(_buffer);

	int sockError = WSASend(m_sessionSocket
		, m_sendOverlapped->GetBuffer()
		, 1
		, &byteSize
		, flag
		, m_sendOverlapped->GetLPOverlapped()
		, nullptr
	);

	if (SOCKET_ERROR == sockError)
	{
		if (WSA_IO_PENDING != WSAGetLastError())
		{
			ServerDebug::GetLastErrorPrint();
			return;
		}
	}

	ServerDebug::LogInfo("Send Packet");
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

	//////////////////////
	// 옵션설정
	//////////////////////

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

	 m_recvOverlapped = new RecvOverlapped(this);
	 m_disconOverlapped = new DisconnectOverlapped(this);
	 m_acceptExOverlapped = new AcceptExOverlapped(this);
	 m_sendOverlapped = new SendOverlapped(this);

	 m_IOCallback = std::bind(&TCPSession::OnCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}


void TCPSession::SetCallBack(RecvCallBack _recvCallBack, CloseCallBack _closeCallBack)
{
	if (nullptr == _recvCallBack)
	{
		ServerDebug::LogError("receive callback is nullptr");
		return;
	}

	if (nullptr == _closeCallBack)
	{
		ServerDebug::LogError("close callback is nullptr");
		return;
	}

	m_recvCallBack = _recvCallBack;
	m_closeCallBack = _closeCallBack;
}
