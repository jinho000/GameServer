#include "JoginResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Login/JoinUI.h"
#include "../../Login/CLoginUI.h"

void JoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("JoginResultPacketHandler"));

	// 회원가입 완료
	if (EJoinResultCode::OK == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Join OK"));
		m_pGameInst->JoinUI->SetVisibility(ESlateVisibility::Hidden);
		m_pGameInst->LoginUI->LoginStatus = TEXT("Join OK");
		return;
	}

	// 아이디 중복
	if (EJoinResultCode::ID_DUPLE == m_packet->JoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("ID is already exist"));
		m_pGameInst->JoinUI->JoinState = TEXT("ID is already exist");
		return;
	}
}

