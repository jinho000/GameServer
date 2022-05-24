#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Play/PlayGameMode.h"

void UDPStartResultPacketHandler::Start()
{
	// �������� ������ �ÿ��̾� ���̵� ����
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->GetPlayer()->SetPlayerID(m_packet->PlayerID);


}
