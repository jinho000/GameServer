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

// 
// �κ� -> ������û(10) -> ����1(10); <-> ::
void UDPStartPacketHandler::Start()
{
	// udp ����� ���� Ŭ���̾�Ʈ endpoint ����
	IPEndPoint clientEndPoint(m_TCPSession->GetRemoteIPEndPoint().GetIPAddress(), m_packet->udpPort);

	// ������ �������� endpoint, player ID ����
	ContentCore::SetUserEndPoint(clientEndPoint);

	std::shared_ptr<ClientPlayer> pClientPlayer = std::make_shared<ClientPlayer>();
	m_packet->PlayerData.PlayerID = pClientPlayer->GetPlayerID();
	pClientPlayer->SetPlayerData(m_packet->PlayerData);
	ContentCore::AddNewPlayer(pClientPlayer);

	// �÷��̾�� ������ �������̵� ����
	// TCP�� �����Ͱ� ������ΰ��Ƿ� ID�� ���޵� �� ��ε�ĳ������ �޴´�
	UDPStartResultPacket packet;
	packet.PlayerID = pClientPlayer->GetPlayerID();

	ServerSerializer sr;
	packet >> sr;
	m_TCPSession->Send(sr.GetBuffer());

	// ������ ���Ӽ���(���߿��� �������� �ٲٱ�)	
	// ĳ���� ������Ŷ ����
	// ���� ���� ��� ĳ������ ������ �����Ѵ�
	{
		SpawnOtherPlayerPacket packet;
		const std::unordered_map<uint64_t, std::shared_ptr<ClientPlayer>>& allPlayer = ContentCore::GetAllPlayer();
		auto iter = allPlayer.begin();
		while (iter != allPlayer.end())
		{
			packet.AllPlayerInfo.push_back(iter->second->GetPlayerData());
			++iter;
		}

		ServerSerializer sr;
		packet >> sr;
		m_TCPSession->GetTCPListener()->BroadCast(sr.GetBuffer());
	}
}
