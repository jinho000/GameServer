// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectUI.h"
#include "Components/ListView.h"

#include "CharacterSelectItemObj.h"
#include "CharacterListItem.h"
#include "../Global/CBlueprintFunctionLibrary.h"

void UCharacterSelectUI::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("Create Character Select UI"));

	CharacterListView = Cast<UListView>(GetWidgetFromName(TEXT("CharacterList")));
	//Inst->CharacterListView_ = CharacterListView_;
	FString testName = TEXT("TestNickName");
	std::string testNameUTF8;
	UCBlueprintFunctionLibrary::FStringToUTF8(testName, testNameUTF8);

	//for (size_t i = 0; i < Inst->Characters_.size(); i++)
	for (size_t i = 0; i < 5; i++)
	{
		//NewCharacterObject->Info = Inst->Characters_[i];
		//UClientBlueprintFunctionLibrary::UTF8ToFString(NewCharacterObject->Info.NickName, NewCharacterObject->ConvertNickName);
		//CharacterListView_->AddItem(NewCharacterObject);
		//CharacterListView_->SetScrollOffset(CharacterListView_->GetNumItems() * 50.0f);

		UCharacterSelectItemObj* itemInfoObj = NewObject<UCharacterSelectItemObj>();
		itemInfoObj->CharacterInfo.nickName = testNameUTF8;
		CharacterListView->AddItem(itemInfoObj);
		CharacterListView->SetScrollOffset(CharacterListView->GetNumItems() * 50.0f);

		UE_LOG(LogTemp, Log, TEXT("Add item to Character listView"));
	}
}

void UCharacterSelectUI::CreateCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Create Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);
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

	FString nickNameFStr;
	UCBlueprintFunctionLibrary::UTF8ToFString(characterInfo->CharacterInfo.nickName, nickNameFStr);
	listItemWidget->NickName = nickNameFStr;

	UE_LOG(LogTemp, Log, TEXT("Complete AddItem NickName: %s"), *nickNameFStr);
}
