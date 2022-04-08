// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterListItem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "../Global/CGameInstance.h"
#include "../Global/CBlueprintFunctionLibrary.h"
#include "../Packets/ClientPackets/Packets.h"
#include "CharacterSelectUI.h"

void UCharacterListItem::SelectCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Select Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);

	// 캐릭터 선택 패킷 전달
	UCGameInstance* Inst = Cast<UCGameInstance>(GetGameInstance());

	std::string nickNameUTF8;
	UCBlueprintFunctionLibrary::FStringToUTF8(NickName, nickNameUTF8);

	SelectCharacterPacket packet;
	packet.SelectCharNickName = nickNameUTF8;

	ServerSerializer sr;
	packet >> sr;
	if (false != Inst->SendBytes(sr.GetBuffer()))
	{
		int a = 0;
	}
}

void UCharacterListItem::CreateCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Create Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);

	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());

	CreateCharacterPacket packet;
	UCBlueprintFunctionLibrary::FStringToUTF8(NickName, packet.NickName);

	ServerSerializer sr;
	packet >> sr;

	gameInst->SendBytes(sr.GetBuffer());

	// item update를 위해 저장
	gameInst->CharacterSelectUI->UpdateItem = this;
}

void UCharacterListItem::DeleteCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Delete Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);

	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());

	DeleteCharacterPacket packet;
	UCBlueprintFunctionLibrary::FStringToUTF8(NickName, packet.NickName);

	ServerSerializer sr;
	packet >> sr;

	gameInst->SendBytes(sr.GetBuffer());

	// item update를 위해 저장
	gameInst->CharacterSelectUI->UpdateItem = this;
}

void UCharacterListItem::Toggle(bool _hide)
{
	UButton* selectBtn = Cast<UButton>(GetWidgetFromName(TEXT("CharacterSelectBtn")));
	UButton* deleteBtn = Cast<UButton>(GetWidgetFromName(TEXT("DeleteBtn")));
	UTextBlock* nickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickName")));
	UEditableTextBox* nickNameInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NickNameInputBox")));
	UButton* createBtn = Cast<UButton>(GetWidgetFromName(TEXT("CreateBtn")));

	if (nullptr == selectBtn || nullptr == deleteBtn || nullptr == nickNameText
		|| nullptr == nickNameInputBox || nullptr == createBtn)
	{
		UE_LOG(LogTemp, Log, TEXT("widget is nullptr"));
		return;
	}

	if (_hide)
	{
		selectBtn->SetVisibility(ESlateVisibility::Hidden);
		deleteBtn->SetVisibility(ESlateVisibility::Hidden);
		nickNameText->SetVisibility(ESlateVisibility::Hidden);
		NickName = FString();

		nickNameInputBox->SetVisibility(ESlateVisibility::Visible);
		createBtn->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		selectBtn->SetVisibility(ESlateVisibility::Visible);
		deleteBtn->SetVisibility(ESlateVisibility::Visible);
		nickNameText->SetVisibility(ESlateVisibility::Visible);

		nickNameInputBox->SetVisibility(ESlateVisibility::Hidden);
		createBtn->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCharacterListItem::HideItem()
{
	UE_LOG(LogTemp, Log, TEXT("Hide Item"));

	Toggle(true);
}

void UCharacterListItem::ShowItem()
{
	UE_LOG(LogTemp, Log, TEXT("Show Item"));

	Toggle(false);
}
