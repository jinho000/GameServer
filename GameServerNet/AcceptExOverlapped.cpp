#include "pch.h"
#include <GameServerBase/ServerDebug.h>

#include "AcceptExOverlapped.h"
#include "TCPSession.h"

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
		return;
	}

	// AcceptEx함수에서 주소값이 같이 옴
	SOCKADDR_IN* pLocalAddr = nullptr;
	SOCKADDR_IN* pRemoteAddr = nullptr;

	int localLen = 0;
	int RemoteLen = 0;

	GetAcceptExSockaddrs(m_buffer,
		0,
		sizeof(sockaddr_in) + 16,
		sizeof(sockaddr_in) + 16,
		(LPSOCKADDR*)&pLocalAddr,
		&localLen,
		(LPSOCKADDR*)&pRemoteAddr,
		&RemoteLen);

	// 바이트 덩어리로 나온다.
	char ArrLocalAddr[4];
	memcpy_s(ArrLocalAddr, 4, &pLocalAddr->sin_addr.s_addr, 4);

	char ArrRemoteAddr[4];
	memcpy_s(ArrRemoteAddr, 4, &pRemoteAddr->sin_addr.s_addr, 4);

	// 세션에 서버, 클라주소 세팅
	m_tcpSession->m_localAddr  = IPEndPoint(pLocalAddr->sin_addr.s_addr, htons(pLocalAddr->sin_port));
	m_tcpSession->m_remoteAddr = IPEndPoint(pRemoteAddr->sin_addr.s_addr, htons(pRemoteAddr->sin_port));
}

void* AcceptExOverlapped::GetBuffer()
{
	return m_buffer;
}


PtrSTCPSession AcceptExOverlapped::GetTCPSession()
{
	return std::dynamic_pointer_cast<TCPSession>(m_tcpSession->shared_from_this());
}
