#include "pch.h"
#include "UDPStartPacketHandler.h"
#include <GameServerCore/ServerCore.h>
#include "PacketHeader.h"

void UDPStartPacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<UDPStartPacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

void UDPStartPacketHandler::Start()
{
	// udp의 endpoint 저장
	ServerCore::SetUserEndPoint(m_clientEndPoint);

	// UDP 시작 패킷 전송
	UDPStartResultPacket packet;
	ServerSerializer sr;
	packet >> sr;
	
	// 방금 접속한 유저만 받도록 수정해야함
	const std::vector<IPEndPoint>& allEndpoint = ServerCore::GetAllUserEndPoint();
	for (const IPEndPoint& userEndPoint : allEndpoint)
	{
		m_UDPSession->Send(sr.GetBuffer(), userEndPoint);
	}
}
