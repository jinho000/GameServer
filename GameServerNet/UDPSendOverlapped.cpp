#include "pch.h"
#include "UDPSendOverlapped.h"
#include "UDPSession.h"

UDPSendOverlapped::UDPSendOverlapped(UDPSession* _udpSession)
	: m_buffer{}
	, m_wsaBuff{}
	, m_numberofBytes()
	, m_udpSession(_udpSession)
{
	memset(m_buffer, 0x00, sizeof(m_buffer));
	m_wsaBuff.buf = m_buffer;
	m_wsaBuff.len = static_cast<ULONG>(sizeof(m_buffer));
	m_numberofBytes = 0;
}

UDPSendOverlapped::~UDPSendOverlapped()
{
}

void UDPSendOverlapped::Clear()
{
	memset(m_buffer, 0x00, sizeof(m_buffer));
	m_wsaBuff.buf = m_buffer;
	m_wsaBuff.len = static_cast<ULONG>(sizeof(m_buffer));
	m_numberofBytes = 0;
}

void UDPSendOverlapped::Excute(BOOL _result, DWORD _byteSize)
{
	// 버퍼를 클리어 후 sendPool에 넣는다
	Clear();

	m_udpSession->OnSendComplete(this);
}

void UDPSendOverlapped::CopyFrom(const std::vector<uint8_t>& _from)
{
	if (sizeof(m_buffer) < _from.size())
	{
		ServerDebug::AssertDebugMsg("send buffer error");
		return;
	}

	memcpy_s(m_wsaBuff.buf, sizeof(m_buffer), &_from[0], _from.size());
	m_wsaBuff.len = static_cast<ULONG>(_from.size());
}

LPDWORD UDPSendOverlapped::GetBufferLength()
{
	return &m_numberofBytes;
}

LPWSABUF UDPSendOverlapped::GetBuffer()
{
	return &m_wsaBuff;
}
