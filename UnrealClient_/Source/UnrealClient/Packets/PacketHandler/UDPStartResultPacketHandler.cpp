#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Play/PlayGameMode.h"

void UDPStartResultPacketHandler::Start()
{
	// 서버에서 생성된 플에이어 아이디 세팅
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->GetPlayer()->SetPlayerID(m_packet->PlayerID);


}
