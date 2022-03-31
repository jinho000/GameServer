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
		ServerDebug::LogError("������ ���õǾ� ���� ���� �������� ��ü");
	}

	// AcceptEx�Լ����� �ּҰ��� ���� ��
}

void* AcceptExOverlapped::GetBuffer()
{
	return m_buffer;
}


TCPSession* AcceptExOverlapped::GetTCPSession() const
{
	return m_tcpSession;
}
