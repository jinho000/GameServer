// Fill out your copyright notice in the Description page of Project Settings.


#include "CChatWindow.h"
#include <Components/ListView.h>

#include "CChatMsgWidget.h"


void UCChatWindow::AddChatMessage(UObject* _chatMsgObj, UUserWidget* _chatMsgWidget)
{
	UE_LOG(LogTemp, Log, TEXT("AddChatMessage"));
	
	UCChatMsgWidget* pMsgWidget = Cast<UCChatMsgWidget>(_chatMsgWidget);
	pMsgWidget->Message = TEXT("Test");
}

void UCChatWindow::OnChatMsgCommitted(const FString& _text, ETextCommit::Type _textType)
{
	UObject* obj = NewObject<UObject>();
	MessageList->AddItem(obj);

	UE_LOG(LogTemp, Log, TEXT("OnChatMsgCommitted"));
}
