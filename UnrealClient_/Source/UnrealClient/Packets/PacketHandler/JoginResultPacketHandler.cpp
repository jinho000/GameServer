#include "JoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>


void JoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("JoginResultPacketHandler"));

	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EJoinResultCode::OK == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Join OK"));
		return;
	}

	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EJoinResultCode::ID_DUPLE == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("ID is already exist"));
		return;
	}
}

