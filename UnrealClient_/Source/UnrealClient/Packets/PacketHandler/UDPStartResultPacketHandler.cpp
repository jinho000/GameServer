#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// ���� ������ �̵�
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

}