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
// 로비 -> 참가요청(10) -> 세션1(10); <-> ::
void UDPStartPacketHandler::Start()
{
	// udp 통신을 위한 클라이언트 endpoint 저장
	IPEndPoint clientEndPoint(m_TCPSession->GetRemoteIPEndPoint().GetIPAddress(), m_packet->udpPort);

	// 스레드 동시접근 endpoint, player ID 저장
	ContentCore::SetUserEndPoint(clientEndPoint);

	std::shared_ptr<ClientPlayer> pClientPlayer = std::make_shared<ClientPlayer>();
	m_packet->PlayerData.PlayerID = pClientPlayer->GetPlayerID();
	pClientPlayer->SetPlayerData(m_packet->PlayerData);
	ContentCore::AddNewPlayer(pClientPlayer);

	// 플레이어에게 생성한 유저아이디 전달
	// TCP는 데이터가 순서대로가므로 ID가 전달된 후 브로드캐스팅을 받는다
	UDPStartResultPacket packet;
	packet.PlayerID = pClientPlayer->GetPlayerID();

	ServerSerializer sr;
	packet >> sr;
	m_TCPSession->Send(sr.GetBuffer());

	// 지금은 게임서버(나중에는 세션으로 바꾸기)	
	// 캐릭터 생성패킷 전달
	// 룸이 가진 모든 캐릭터의 정보를 전달한다
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
