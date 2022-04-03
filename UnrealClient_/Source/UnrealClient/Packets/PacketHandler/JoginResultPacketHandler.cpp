#include "JoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>


void JoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("JoginResultPacketHandler"));

	// 서버로부터 로그인패킷 정상전달이 확인되면 다음 레벨로 이동
	if (EResultCode::OK == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Join OK"));

	}

	// 서버로부터 로그인패킷 정상전달이 확인되면 다음 레벨로 이동
	if (EResultCode::ID_ERROR == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("ID is already exist"));

	}
}

