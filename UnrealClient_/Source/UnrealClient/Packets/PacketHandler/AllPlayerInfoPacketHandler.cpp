#include "AllPlayerInfoPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Play/PlayGameMode.h"

class Test
{};

class D : public Test
{};

void AllPlayerInfoPacketHandler::Start()
{
	// �ٸ� ������ ������ �޾� ����
	APlayGameMode* pPlayGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pPlayGameMode->UpdateOtherPlayerInfo(m_packet->AllPlayerInfo);
}

