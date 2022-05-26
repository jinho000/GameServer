#include "GameMatchPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Lobby/LobbyGameMode.h"


void GameMatchPacketHandler::Start()
{
	// 플레이 레벨 이동
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

	// 게임로비에서 보낸 UDP시작 패킷결과 받아 저장
	// 세션번호, 플레이어 인덱스, 다른 플레이어 인덱스 저장
	m_pGameInst->SetSessionIdx(m_packet->sessionIdx);
	m_pGameInst->SetPlayerIdx(m_packet->playerIdx);
	
	std::vector<uint64_t> otherPlayerID;
	for (size_t i = 0; i < m_packet->AllPlayerInfo.size(); i++)
	{
		// 다른 플레이어의 아이디만 저장
		if (m_packet->AllPlayerInfo[i].PlayerID == m_pGameInst->GetPlayerID())
		{
			continue;
		}

		otherPlayerID.push_back(m_packet->AllPlayerInfo[i].PlayerID);
	}

	m_pGameInst->SetOtherPlayerID(otherPlayerID);
}
