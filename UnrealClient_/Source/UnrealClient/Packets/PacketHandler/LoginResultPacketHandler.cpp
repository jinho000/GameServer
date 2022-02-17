#include "LoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>

LoginResultPacketHandler::LoginResultPacketHandler(const std::shared_ptr<LoginResultPacket>& _packet)
	: m_packet(_packet)
{
}

LoginResultPacketHandler::~LoginResultPacketHandler()
{
}

void LoginResultPacketHandler::Start()
{
	// 서버로부터 로그인패킷 정상전달이 확인되면 다음 레벨로 이동
	if (EResultCode::OK == m_packet->GetResultCode())
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Login Result Packet"))
		UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));
	}
}

