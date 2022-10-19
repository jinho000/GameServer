#include "pch.h"
#include "UDPStartPacketHandler.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/ServerCore.h>
#include "ContentManager.h"
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

	// ContentManager접근 게임로비에 endpoint, player ID 저장
	std::shared_ptr<ClientPlayer> pClientPlayer = std::make_shared<ClientPlayer>();
	ContentManager::GetInst()->AddUserToLobby(pClientPlayer, clientEndPoint, m_TCPSession);

	// 플레이어에게 생성한 유저아이디 전달
	UDPStartResultPacket packet;
	packet.PlayerID = pClientPlayer->GetPlayerID();

	ServerSerializer sr;
	packet >> sr;
	m_TCPSession->Send(sr.GetBuffer());
}
