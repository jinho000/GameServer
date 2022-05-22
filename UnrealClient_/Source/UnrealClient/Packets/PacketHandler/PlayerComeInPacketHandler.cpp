#include "PlayerComeInPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void PlayerComeInPacketHandler::Start()
{
	// 플레이어가 이미 접속해 있을때 새로온 유저의 정보를 받아 세팅
	APlayGameMode* PGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	PGameMode->SpawnNewOtherPlayer(m_packet->PlayerData.PlayerID);
}

