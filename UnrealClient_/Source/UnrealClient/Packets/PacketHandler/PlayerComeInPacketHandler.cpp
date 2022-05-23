#include "PlayerComeInPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void PlayerComeInPacketHandler::Start()
{
	// 플레이어가 이미 접속해 있을때 새로온 유저의 정보를 받아 세팅
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->SpawnOtherPlayer(m_packet->PlayerData);
}

