#include "pch.h"
#include "UDPRecvOverlapped.h"
#include "UDPSession.h"

UDPRecvOverlapped::UDPRecvOverlapped(UDPSession* _udpSession)
	: m_buffer{}
	, m_wsaBuffer{}
	, m_numberofBytes()
	, m_udpSession(_udpSession)
{
	memset(m_buffer, 0x00, sizeof(m_buffer));
	m_wsaBuffer.buf = m_buffer;
	m_wsaBuffer.len = static_cast<ULONG>(sizeof(m_buffer));
	m_numberofBytes = 0;
}


UDPRecvOverlapped::~UDPRecvOverlapped()
{
}

void UDPRecvOverlapped::Clear()
{
	memset(m_buffer, 0x00, sizeof(m_buffer));
	m_wsaBuffer.len = sizeof(m_buffer);
	m_wsaBuffer.buf = m_buffer;
}

void UDPRecvOverlapped::Excute(BOOL Result, DWORD _ByteSize)
{
	// tcp는 접속한 클라이언트마다 session을 가짐
	// udp는 server core가 세션을 가짐
	// recv이벤트시 각 스레드에서 Excute 호출
	// 하나의 udp세션을 여러 스레드에서 사용할 가능성 있음


	// UDP는 접속을 끊을 필요가 없음
	// recvCallback 호출 필요없이 다시 리시브요청 실행
	if (0 == _ByteSize)
	{
		m_udpSession->RequestRecv();
		return;
	}

	m_udpSession->OnRecv(m_buffer, _ByteSize);
}

void* UDPRecvOverlapped::GetBuffer()
{
	return m_buffer;
}

LPWSABUF UDPRecvOverlapped::GetWSABuffer()
{
	return &m_wsaBuffer;
}

LPDWORD UDPRecvOverlapped::GetBufferLength()
{
	return &m_numberofBytes;
}
