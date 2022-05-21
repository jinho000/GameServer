#include "pch.h"
#include "UDPStartPacketHandler.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/ServerCore.h>
#include "ContentCore.h"
#include "PacketHeader.h"
#include "ClientPlayer.h"

void UDPStartPacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<UDPStartPacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

void UDPStartPacketHandler::Start()
{
	// udp 통신을 위한 클라이언트 endpoint 저장
	IPEndPoint clientEndPoint(m_TCPSession->GetRemoteIPEndPoint().GetIPAddress(), m_packet->udpPort);

	// 스레드 동시접근
	// endpoint, player ID 저장
	ContentCore::SetUserEndPoint(clientEndPoint);

	std::shared_ptr<ClientPlayer> pClientPlayer = std::make_shared<ClientPlayer>();
	ContentCore::AddNewPlayer(pClientPlayer);

	// UDP 시작 패킷 전송
	UDPStartResultPacket packet;
	packet.PlayerID = pClientPlayer->GetPlayerID();

	ServerSerializer sr;
	packet >> sr;
	
	m_TCPSession->Send(sr.GetBuffer());
}
