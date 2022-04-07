#include "CreateCharacterResultPacketHandler.h"
#include "../../Global/CGameInstance.h"
#include "../../CharacterSelect/CharacterSelectItemObj.h"
#include "../../Global/CBlueprintFunctionLibrary.h"
#include "../../CharacterSelect/CharacterSelectUI.h"
#include "../../CharacterSelect/CharacterListItem.h"

#include "Components/ListView.h"


void CreateCharacterResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("CreateCharacterResultPacketHandler"));

	if (ECreateCharacterResultCode::ID_DULE == m_packet->ResultCode)
	{
		m_pGameInst->CharacterSelectUI->State = TEXT("ID Fail");
		UE_LOG(LogTemp, Log, TEXT("ID Fail"));
		return;
	}

	if (ECreateCharacterResultCode::OK != m_packet->ResultCode)
	{
		m_pGameInst->CharacterSelectUI->State = TEXT("Create Character Fail");
		UE_LOG(LogTemp, Log, TEXT("Create Character Fail"));
		return;
	}

	// 게임모드인스턴스에 캐릭터 정보 추가
	m_pGameInst->UserCharacterList.push_back(m_packet->CharacterInfo);
	
	
	// UI 리스트뷰 갱신
	UE_LOG(LogTemp, Log, TEXT("Update UI Listview"));
	FString nickName;
	UCBlueprintFunctionLibrary::UTF8ToFString(m_packet->CharacterInfo.NickName, nickName);
	UE_LOG(LogTemp, Log, TEXT("NickName: %s"), *nickName);

	m_pGameInst->CharacterSelectUI->State = TEXT("Create Character OK");
	m_pGameInst->CharacterSelectUI->UpdateItem->ShowItem();
	m_pGameInst->CharacterSelectUI->UpdateItem = nullptr;
}
