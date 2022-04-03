#include "JoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>


void JoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("JoginResultPacketHandler"));

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

