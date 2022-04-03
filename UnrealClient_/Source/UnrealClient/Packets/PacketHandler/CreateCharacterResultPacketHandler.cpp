#include "CreateCharacterResultPacketHandler.h"
#include "../../Global/CGameInstance.h"
#include "../../CharacterSelect/CharacterSelectItemObj.h"
#include "../../Global/CBlueprintFunctionLibrary.h"
#include "Components/ListView.h"


void CreateCharacterResultPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("CreateCharacterResultPacketHandler"));

	if (EResultCode::OK != m_packet->ResultCode)
	{
		UE_LOG(LogTemp, Log, TEXT("Create Character Fail"));
		return;
	}

	// 게임모드인스턴에 캐릭터 정보 추가
	m_pGameInst->UserCharacterList.push_back(m_packet->CharacterInfo);
	
	
	// UI 리스트뷰 추가
	UE_LOG(LogTemp, Log, TEXT("Add Character to UI Listview"));
	FString nickName;
	UCBlueprintFunctionLibrary::UTF8ToFString(m_packet->CharacterInfo.NickName, nickName);
	UE_LOG(LogTemp, Log, TEXT("NickName: %s"), *nickName);

	UCharacterSelectItemObj* NewCharacterObject = NewObject<UCharacterSelectItemObj>();
	NewCharacterObject->CharacterInfo = m_packet->CharacterInfo;
	m_pGameInst->CharacterSelectUIListView->AddItem(NewCharacterObject);
	m_pGameInst->CharacterSelectUIListView->SetScrollOffset(m_pGameInst->CharacterSelectUIListView->GetNumItems() * 50.0f);

}
