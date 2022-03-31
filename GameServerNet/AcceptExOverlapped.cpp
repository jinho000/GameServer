#include "pch.h"
#include "AcceptExOverlapped.h"
#include <GameServerBase/ServerDebug.h>

AcceptExOverlapped::AcceptExOverlapped(TCPSession* _tcpSession)
	: m_buffer{}
	, m_tcpSession(_tcpSession)
{
}

void AcceptExOverlapped::Excute(BOOL _result, DWORD _byteSize)
{
	if (nullptr == m_tcpSession)
	{
		ServerDebug::LogError("세션이 세팅되어 있지 않은 오버랩드 객체");
	}

	// AcceptEx함수에서 주소값이 같이 옴
}

void* AcceptExOverlapped::GetBuffer()
{
	return m_buffer;
}


TCPSession* AcceptExOverlapped::GetTCPSession() const
{
	return m_tcpSession;
}
