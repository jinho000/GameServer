#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// ���� ������ �̵�
	//UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));

	// udp echo test
	PlayerUpdatePacket packet;
	ServerSerializer sr;
	packet >> sr;

	m_pGameInst->SendUDP(sr.GetBuffer());
}
