#include "pch.h"
#include "TCPSession.h"
#include "GameServerBase/ServerUnique.h"

TCPSession::TCPSession()
	: m_conectId(ServerUnique::GetNextUniqueId())
	, m_sessionSocket(NULL)
{
}

TCPSession::~TCPSession()
{
}

TCPSession::TCPSession(TCPSession&& _other) noexcept
{
}

bool TCPSession::Initialize()
{
	return false;
}

SOCKET TCPSession::GetSessionSocket() const
{
	return m_sessionSocket;
}

__int64 TCPSession::GetSessionID() const
{
	return m_conectId;
}
