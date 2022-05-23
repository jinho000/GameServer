#include "pch.h"
#include "PlayerComeInPacketHandler.h"
#include <GameServerNet/TCPSession.h>
#include "ContentCore.h"

void PlayerComeInPacketHandler::Start()
{
	// 클라이언트는 플레이 레벨에 진입 후 전달해야한다
	// 레벨 진입전 전송하면 다른 유저가 있는 정보를 받아 생성 후 다음레벨로 넘어가가게됨


	// 다른 플레이어에게 현재 접속한 유저 알리기
	// 현재 접속한 유저는 제외하고 보내야한다
	ServerSerializer sr;
	*m_packet >> sr;
	m_TCPSession->GetTCPListener()->BroadCast(sr.GetBuffer(), m_TCPSession);
	

	// 방금 들어온 유저의 데이터 정보 저장하기
	// ContentCore에 저장하기
	// 
	// 서버에서 클라이언트 플레이어 객체 생성시점과 초기화시점이 같지 않음
	ContentCore::SetPlayerData(m_packet->PlayerData);

	
	// 방금 접속한 유저에게 접속해있는 다른 유저에 대한 정보 보내기
	// 지금은 게임서버(나중에는 세션으로 바꾸기)
	{
		const std::unordered_map<uint64_t, std::shared_ptr<ClientPlayer>>& allPlayer = ContentCore::GetAllPlayer();
		AllPlayerInfoPacket packet;
		auto iter = allPlayer.begin();
		while (iter != allPlayer.end())
		{
			packet.AllPlayerInfo.push_back(iter->second->GetPlayerData());
			++iter;
		}

		ServerSerializer sr;
		packet >> sr;
		m_TCPSession->Send(sr.GetBuffer());
	}
	
}
