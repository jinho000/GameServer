#include "GameMatchPacketHandler.h"
#include <Kismet/GameplayStatics.h>

void GameMatchPacketHandler::Start()
{
	// �÷��� ���� �̵�
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

}
