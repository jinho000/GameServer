#include "PlayerComeInPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

void PlayerComeInPacketHandler::Start()
{
	// �÷��̾ �̹� ������ ������ ���ο� ������ ������ �޾� ����
	APlayGameMode* PGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	PGameMode->SpawnNewOtherPlayer(m_packet->PlayerData.PlayerID);
}

