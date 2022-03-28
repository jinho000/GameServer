#include "JoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>

JoginResultPacketHandler::JoginResultPacketHandler(const std::shared_ptr<JoginResultPacket>& _packet)
	: m_packet(_packet)
{
}

JoginResultPacketHandler::~JoginResultPacketHandler()
{
}

void JoginResultPacketHandler::Start()
{
	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EResultCode::OK == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Join OK"));

	}

	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EResultCode::ID_ERROR == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("ID is already exist"));

	}
}

