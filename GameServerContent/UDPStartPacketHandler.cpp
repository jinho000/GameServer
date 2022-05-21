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
	// udp ����� ���� Ŭ���̾�Ʈ endpoint ����
	IPEndPoint clientEndPoint(m_TCPSession->GetRemoteIPEndPoint().GetIPAddress(), m_packet->udpPort);

	// ������ ��������
	// endpoint, player ID ����
	ContentCore::SetUserEndPoint(clientEndPoint);

	std::shared_ptr<ClientPlayer> pClientPlayer = std::make_shared<ClientPlayer>();
	ContentCore::AddNewPlayer(pClientPlayer);

	// UDP ���� ��Ŷ ����
	UDPStartResultPacket packet;
	packet.PlayerID = pClientPlayer->GetPlayerID();

	ServerSerializer sr;
	packet >> sr;
	
	m_TCPSession->Send(sr.GetBuffer());
}
