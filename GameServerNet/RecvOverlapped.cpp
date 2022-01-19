#include "pch.h"
#include "RecvOverlapped.h"
#include "TCPSession.h"

RecvOverlapped::RecvOverlapped(PtrSTCPSession _tcpSession)
	: m_Buffer{}
	, m_wsaBuffer{}
	, m_tcpSession(_tcpSession)
{
}

RecvOverlapped::~RecvOverlapped()
{
}

void RecvOverlapped::Clear()
{
	memset(m_Buffer, 0x00, sizeof(m_Buffer));
	m_wsaBuffer.len = sizeof(m_Buffer);
	m_wsaBuffer.buf = m_Buffer;
}

void RecvOverlapped::Excute(BOOL Result, DWORD _ByteSize)
{
	if (0 == _ByteSize)
	{
		// 立加捞 辆丰等 版快
		//m_tcpSession->
		return;
	}

	m_tcpSession->OnRecv(m_Buffer, _ByteSize);
}

void* RecvOverlapped::GetBuffer()
{
	return m_Buffer;
}

LPWSABUF RecvOverlapped::GetWSABuffer()
{
	return &m_wsaBuffer;
}

PtrSTCPSession RecvOverlapped::GetTCPSession()
{
	return m_tcpSession;
}
