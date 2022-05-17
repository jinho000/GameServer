#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// 다음 레벨로 이동
	//UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

	// udp echo test
	PlayerUpdatePacket packet;
	ServerSerializer sr;
	packet >> sr;

	m_pGameInst->SendUDP(sr.GetBuffer());
}
