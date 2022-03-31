#include "pch.h"
#include "DisconnectOverlapped.h"
#include "TCPSession.h"

DisconnectOverlapped::DisconnectOverlapped(TCPSession* _tcpSession)
	: m_tcpSession(_tcpSession)
{
}

DisconnectOverlapped::~DisconnectOverlapped()
{
}

DisconnectOverlapped::DisconnectOverlapped(DisconnectOverlapped&& _other) noexcept
{
}

void DisconnectOverlapped::Excute(BOOL _result, DWORD _byteSize)
{
	if (nullptr != m_tcpSession)
	{
		//m_tcpSession->C
		m_tcpSession->UnregisterSession();
	}
}
