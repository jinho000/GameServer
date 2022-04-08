// Fill out your copyright notice in the Description page of Project Settings.


#include "CChatWindow.h"
#include <Components/ListView.h>

#include "CChatMsgWidget.h"
#include "CChatMessage.h"
#include "../../Packets/ClientPackets/ClientToServer.h"
#include "../../Packets/ClientPackets/ServerToClient.h"
#include "../../Packets/ClientPackets/ServerAndClient.h"
#include "../../Packets/ClientPackets/ServerSerializer.h"
#include "../../Global/CGameInstance.h"

void UCChatWindow::NativeConstruct()
{
	UCGameInstance* Inst = Cast<UCGameInstance>(GetGameInstance());
	Inst->SetChatWindow(this);
}

// 채팅리스트에 채팅위젯이 추가된 경우 실행 함수
void UCChatWindow::AddChatMessage(UObject* _chatMsgObj, UUserWidget* _chatMsgWidget)
{
	UE_LOG(LogTemp, Log, TEXT("AddChatMessage"));

	UCChatMessage* pChatMessage = Cast<UCChatMessage>(_chatMsgObj);
	UCChatMsgWidget* pMsgWidget = Cast<UCChatMsgWidget>(_chatMsgWidget);

	// 채팅으로 입력된 경우만 처리
	if (nullptr == pChatMessage || nullptr == pMsgWidget)
	{
		return;
	}

	FString msg = pChatMessage->GetChatMessage();
	pMsgWidget->Message = msg;
}

void UCChatWindow::AddChatMessage(UCChatMessage* _chatMassage)
{
	MessageList->AddItem(_chatMassage);
	MessageList->SetScrollOffset(MessageList->GetNumItems() * 50.0f);
}

void UCChatWindow::OnChatMsgCommitted(const FString& _chatMessage, ETextCommit::Type _commitType)
{
	// enter 입력인경우만 처리
	if (ETextCommit::Type::OnEnter != _commitType)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("OnChatMsgCommitted"));
	
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	ChatMessagePacket packet;
	FCharacterInfo currCharacter = gameInst->SelectCharacter;
	packet.NickName = currCharacter.NickName;
	packet.Message = FTCHARToUTF8(*_chatMessage).Get();

	ServerSerializer sr;
	packet >> sr;
	gameInst->SendBytes(sr.GetBuffer());

	// 입력 비우기
	InputText.Empty();

	FString nickName = FUTF8ToTCHAR(packet.NickName.c_str()).Get();
	UE_LOG(LogTemp, Log, TEXT("Send NickName: %s"), *nickName);
	UE_LOG(LogTemp, Log, TEXT("Send Message: %s"), *_chatMessage);
}