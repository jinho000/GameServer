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
	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EResultCode::OK == m_packet->GetResultCode())
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Login Result Packet"))
		UGameplayStatics::OpenLevel(m_pWorld, TEXT("PlayLevel"));
	}
}

