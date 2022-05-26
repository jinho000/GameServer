#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Lobby/LobbyGameMode.h"
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// ���ӷκ񿡼� ���� UDP���� ��Ŷ��� �޾� ����
	ALobbyGameMode* pLobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pLobbyGameMode->SetPlayerID(m_packet->PlayerID);
}
