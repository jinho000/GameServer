#include "UDPStartResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Lobby/LobbyGameMode.h"
#include "../../Global/CGameInstance.h"

void UDPStartResultPacketHandler::Start()
{
	// 게임로비에서 보낸 UDP시작 패킷결과 받아 저장
	m_pGameInst->SetPlayerID(m_packet->PlayerID);
}
