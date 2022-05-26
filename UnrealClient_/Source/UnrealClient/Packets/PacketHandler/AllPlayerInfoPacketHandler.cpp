#include "AllPlayerInfoPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void AllPlayerInfoPacketHandler::Start()
{
	// 다른 유저의 정보를 받아 세팅
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->UpdateOtherPlayerInfo(m_packet->AllPlayerInfo);
}

