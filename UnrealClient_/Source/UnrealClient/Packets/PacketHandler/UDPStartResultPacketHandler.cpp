#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Lobby/LobbyGameMode.h"

void UDPStartResultPacketHandler::Start()
{
	// ���ӷκ񿡼� ���� UDP���� ��Ŷ��� �޾� ����
	ALobbyGameMode* pLobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pLobbyGameMode->SetPlayerID(m_packet->PlayerID);
}
