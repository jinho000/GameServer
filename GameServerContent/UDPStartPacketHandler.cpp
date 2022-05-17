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
	

	m_UDPSession->Send(sr.GetBuffer(), m_clientEndPoint);

}
