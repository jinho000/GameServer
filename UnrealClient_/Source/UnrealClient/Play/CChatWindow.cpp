// Fill out your copyright notice in the Description page of Project Settings.


#include "CChatWindow.h"
#include <Components/ListView.h>

#include "CChatMsgWidget.h"
#include "CChatMessage.h"

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

void UCChatWindow::OnChatMsgCommitted(const FString& _text, ETextCommit::Type _commitType)
{
	UE_LOG(LogTemp, Log, TEXT("OnChatMsgCommitted"));

	// enter 입력인경우만 처리
	if (ETextCommit::Type::OnEnter != _commitType)
	{
		return;
	}

	UCChatMessage* pChatMessage = NewObject<UCChatMessage>();
	pChatMessage->Init(TEXT("UserID"), _text);

	MessageList->AddItem(pChatMessage);

	// 입력 비우기
	InputText.Empty();
}
