#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// 다음 레벨로 이동
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

	m_pGameInst->SetPlayerID(m_packet->PlayerID);	
}
