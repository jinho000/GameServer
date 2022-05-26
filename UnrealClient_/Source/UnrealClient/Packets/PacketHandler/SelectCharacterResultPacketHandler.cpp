#include "SelectCharacterResultPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Global/CBlueprintFunctionLibrary.h"
#include "../../Global/CGameInstance.h"
#include "../../Packets/ClientPackets/Packets.h"

void SelectCharacterResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("SelectCharacterResultPacketHandler"));

	if (EResultCode::OK != m_packet->ResultCode)
	{
		m_pGameInst->LoginProcess = false;
		UE_LOG(LogTemp, Log, TEXT("Result Code FAIL"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Result Code OK"));

	// 로딩이건 뭐건 고려 안함.
	// 지금 클라가 할게 없음
	// 물어봐야지
	// 로딩 고려하시면 됩니다.
	FString nickName;
	UCBlueprintFunctionLibrary::UTF8ToFString(m_packet->SelectCharNickName, nickName);

	UE_LOG(LogTemp, Log, TEXT("Check Packet NickName"));
	const std::vector<FCharacterInfo>& characterList = m_pGameInst->UserCharacterList;
	for (size_t i = 0; i < characterList.size(); i++)
	{
		if (characterList[i].NickName == m_packet->SelectCharNickName)
		{
			// 전달받은 패킷의 닉네임 검증 완료
			UE_LOG(LogTemp, Log, TEXT("Check NickName OK: %s"), *nickName);
			m_pGameInst->SelectCharacter = characterList[i];
			m_pGameInst->LoginProcess = true;

			UE_LOG(LogTemp, Log, TEXT("GameSession Number %d"), (int)m_packet->GameSessionType);

			// 다음레벨 이동
			UGameplayStatics::OpenLevel(m_pWorld, TEXT("Lobby"));
			return;
		}
	}

	// 보낸 캐릭터 이름과 전달받은 캐릭터이름이 다르므로 선택실패
	// 초기 로그인화면으로 돌아간다
	UE_LOG(LogTemp, Log, TEXT("Check NickName FAIL"));
	UE_LOG(LogTemp, Error, TEXT("%S(%u) > Charcter Client Data FAIL"), __FUNCTION__, __LINE__);
	m_pGameInst->LoginProcess = false;
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("LoginLevel"));
}
