#include "LoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"

LoginResultPacketHandler::LoginResultPacketHandler(const std::shared_ptr<LoginResultPacket>& _packet)
	: m_packet(_packet)
{
}

LoginResultPacketHandler::~LoginResultPacketHandler()
{
}

void LoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("LoginResultPacketHandler"));

	// 서버로부터 로그인패킷 정상전달이 확인되면 다음 레벨로 이동
	if (EResultCode::OK == m_packet->LoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Login Result Packet"));
		UE_LOG(LogTemp, Log, TEXT("Loading User Character List"));
		//UGameplayStatics::OpenLevel(m_pWorld, TEXT("CharacterSelect"));		;
		m_pGameInst->LoginProcess = true;
		return;
	}

	// 로그인 실패
	UE_LOG(LogTemp, Log, TEXT("Login Fail"));
	m_pGameInst->LoginProcess = false;
}

