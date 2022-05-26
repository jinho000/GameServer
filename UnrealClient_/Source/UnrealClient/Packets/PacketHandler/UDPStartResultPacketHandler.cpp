#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Lobby/LobbyGameMode.h"

void UDPStartResultPacketHandler::Start()
{
	// 게임로비에서 보낸 UDP시작 패킷결과 받아 저장
	ALobbyGameMode* pLobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(m_pWorld));
	pLobbyGameMode->SetPlayerID(m_packet->PlayerID);
}
