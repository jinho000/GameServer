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

	// �����κ��� �α�����Ŷ ���������� Ȯ�εǸ� ���� ������ �̵�
	if (EResultCode::OK == m_packet->LoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Login Result Packet"));
		UE_LOG(LogTemp, Log, TEXT("Loading User Character List"));
		//UGameplayStatics::OpenLevel(m_pWorld, TEXT("CharacterSelect"));		;
		m_pGameInst->LoginProcess = true;
		return;
	}

	// �α��� ����
	UE_LOG(LogTemp, Log, TEXT("Login Fail"));
	m_pGameInst->LoginProcess = false;
}

