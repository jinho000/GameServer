#include "AllPlayerInfoPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void AllPlayerInfoPacketHandler::Start()
{
	// 플레이어가 접속했을때 이미 있는 유저의 정보를 받아 세팅
	
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));

	const std::vector<FPlayerUpdateData>& allPlayerInfo = m_packet->AllPlayerInfo;
	for (const FPlayerUpdateData& playerInfo : allPlayerInfo)
	{
		// 모든 플레이어의 정보가 들어오므로 내 정보는 빼고 처리해야한다
		if (playerInfo.PlayerID == m_pGameInst->GetPlayerID())
		{
			continue;
		}

		pPlayGameMode->SpawnOtherPlayer(playerInfo);
	}
}

