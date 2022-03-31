#include "pch.h"
#include "SendOverlapped.h"
#include "TCPSession.h"

SendOverlapped::SendOverlapped()
	: m_buffer{}
	, m_wsaBuff{}
	, m_tcpSession(nullptr)

{
}

SendOverlapped::~SendOverlapped()
{
}

void SendOverlapped::SetTCPSession(TCPSession* _tcpSession)
{
	m_tcpSession = _tcpSession;
}

void SendOverlapped::Excute(BOOL _result, DWORD _byteSize)
{
	m_tcpSession->OnSendComplete(this);
}

void SendOverlapped::New(size_t _maxBufferLength)
{
	m_buffer.resize(_maxBufferLength);
	m_wsaBuff.buf = &m_buffer[0];
	m_wsaBuff.len = static_cast<ULONG>(m_buffer.size());
}

void SendOverlapped::CopyFrom(const std::vector<uint8_t>& _from)
{
	New(_from.size());
	std::copy(_from.begin(), _from.end(), m_buffer.begin());
}

int SendOverlapped::GetMaxBufferLength()
{
	return static_cast<int>(m_buffer.size());
}

LPWSABUF SendOverlapped::GetBuffer()
{
	return &m_wsaBuff;
}
