// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectUI.h"
#include "Components/ListView.h"

#include "CharacterSelectItemObj.h"
#include "CharacterListItem.h"
#include "../Global/CBlueprintFunctionLibrary.h"
#include "../Global/CGameInstance.h"
#include "../Packets/ClientPackets/Packets.h"
#include "../Global/CGameInstance.h"



void UCharacterSelectUI::NativeConstruct()
{
	UpdateItem = nullptr;

	UE_LOG(LogTemp, Log, TEXT("CharacterSelectUI NativeContruct"));

	UCGameInstance* Inst = Cast<UCGameInstance>(GetGameInstance());
	Inst->CharacterSelectUI = this;

	// UI에서 캐릭터리스트뷰 가져오기
	CharacterListView = Cast<UListView>(GetWidgetFromName(TEXT("CharacterList")));
	Inst->CharacterSelectUIListView = CharacterListView;
	

	// 캐릭터리스트를 UI 캐릭터 리스트뷰에 추가
	const std::vector<FCharacterInfo>& userCharacterList = Inst->UserCharacterList;
	UE_LOG(LogTemp, Log, TEXT("Get User CharacterList, list count: %d"), userCharacterList.size());

	int userCharacterListSize = userCharacterList.size();
	for (size_t i = 0; i < userCharacterListSize; i++)
	{
		UCharacterSelectItemObj* newItemInfoObj = NewObject<UCharacterSelectItemObj>();
		newItemInfoObj->CharacterInfo = userCharacterList[i];
		CharacterListView->AddItem(newItemInfoObj);
		CharacterListView->SetScrollOffset(CharacterListView->GetNumItems() * 50.0f);
	}

	// 캐릭터 개수를 5개로 제한
	for (size_t i = 0; i < 5 - userCharacterListSize; i++)
	{
		UCharacterSelectItemObj* newItemInfoObj = NewObject<UCharacterSelectItemObj>();
		CharacterListView->AddItem(newItemInfoObj);
		CharacterListView->SetScrollOffset(CharacterListView->GetNumItems() * 50.0f);
	}
}

void UCharacterSelectUI::AddItemToListEvent(UObject* _object, UUserWidget* _widget)
{
	UCharacterSelectItemObj* characterInfo = Cast<UCharacterSelectItemObj>(_object);
	UCharacterListItem* listItemWidget = Cast<UCharacterListItem>(_widget);

	if (nullptr == characterInfo)
	{
		return;
	}

	if (nullptr == listItemWidget)
	{
		return;
	}

	if (characterInfo->CharacterInfo.Index == -1)
	{
		UE_LOG(LogTemp, Log, TEXT("User Character Empty"));

		listItemWidget->HideItem();
		return;
	}

	FString nickNameFStr;
	UCBlueprintFunctionLibrary::UTF8ToFString(characterInfo->CharacterInfo.NickName, nickNameFStr);
	listItemWidget->NickName = nickNameFStr;
	listItemWidget->ShowItem();

	UE_LOG(LogTemp, Log, TEXT("Complete AddItem NickName: %s"), *nickNameFStr);
}

