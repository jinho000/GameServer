#include "LoginResultPacketHandler.h"	
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"
#include "../../Login/CLoginUI.h"


void LoginResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("LoginResultPacketHandler"));

	// 서버로부터 로그인패킷 정상전달이 확인
	if (ELoginResultCode::OK == m_packet->LoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Login Result Packet"));
		UE_LOG(LogTemp, Log, TEXT("Loading User Character List"));
		m_pGameInst->LoginProcess = true;

		// UDP포트 받아오기
		m_pGameInst->SetUDPEndPoint(m_packet->UDPPort);

		return;
	}


	// 로그인 실패
	m_pGameInst->LoginProcess = false;

	// 아이디 없음
	if (ELoginResultCode::ID_ERROR == m_packet->LoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("ID Fail"));
		m_pGameInst->LoginUI->LoginStatus = TEXT("ID Fail");
		return;
	}

	// 비밀번호가 일치하지 않음
	if (ELoginResultCode::PW_ERROR == m_packet->LoginResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Password Fail"));
		m_pGameInst->LoginUI->LoginStatus = TEXT("Password Fail");
		return;
	}
}

