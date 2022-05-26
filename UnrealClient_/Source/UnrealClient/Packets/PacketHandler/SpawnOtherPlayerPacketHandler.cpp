#include "SpawnOtherPlayerPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void SpawnOtherPlayerPacketHandler::Start()
{
	// 접속해있는 모든 유저가 캐릭터 생성패킷을 받는다
	//APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));

	//const std::vector<FPlayerUpdateData>& allPlayerInfo = m_packet->AllPlayerInfo;
	//for (const FPlayerUpdateData& playerInfo : allPlayerInfo)
	//{
	//	// 모든 플레이어의 정보가 들어오므로 내 정보는 빼고 처리해야한다
	//	if (playerInfo.PlayerID == m_pGameInst->GetPlayerID())
	//	{
	//		continue;
	//	}

	//	pPlayGameMode->SpawnOtherPlayer(playerInfo);
	//}
}

