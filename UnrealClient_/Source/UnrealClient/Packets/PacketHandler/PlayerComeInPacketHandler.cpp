#include "PlayerComeInPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void PlayerComeInPacketHandler::Start()
{
	// �÷��̾ �̹� ������ ������ ���ο� ������ ������ �޾� ����
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->SpawnOtherPlayer(m_packet->PlayerData);
}

