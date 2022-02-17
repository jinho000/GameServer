// Fill out your copyright notice in the Description page of Project Settings.


#include "CChatWindow.h"
#include <Components/ListView.h>

#include "CChatMsgWidget.h"
#include "CChatMessage.h"
#include "../Packets/ClientPackets/ChatMessagePacket.h"
#include "../Packets/ClientSerializer.h"
#include "../Global/CGameInstance.h"

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
	ChatMessagePacket packet(gameInst->GetUserID(), _chatMessage);
	ClientSerializer sr;
	packet >> sr;

	UE_LOG(LogTemp, Log, TEXT("Send id: %s"), *gameInst->GetUserID());
	UE_LOG(LogTemp, Log, TEXT("Send Message: %s"), *_chatMessage);
	gameInst->SendBytes(sr.GetBuffer());

	//UCChatMessage* pChatMessage = NewObject<UCChatMessage>();
	//pChatMessage->Init(gameInst->GetUserID(), _text);
	//MessageList->AddItem(pChatMessage);


	// 입력 비우기
	InputText.Empty();
}
