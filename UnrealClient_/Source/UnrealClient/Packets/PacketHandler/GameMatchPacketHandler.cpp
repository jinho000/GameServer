#include "GameMatchPacketHandler.h"
#include <Kismet/GameplayStatics.h>

void GameMatchPacketHandler::Start()
{
	// 플레이 레벨 이동
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

}
