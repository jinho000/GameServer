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

// ä�ø���Ʈ�� ä�������� �߰��� ��� ���� �Լ�
void UCChatWindow::AddChatMessage(UObject* _chatMsgObj, UUserWidget* _chatMsgWidget)
{
	UE_LOG(LogTemp, Log, TEXT("AddChatMessage"));

	UCChatMessage* pChatMessage = Cast<UCChatMessage>(_chatMsgObj);
	UCChatMsgWidget* pMsgWidget = Cast<UCChatMsgWidget>(_chatMsgWidget);

	// ä������ �Էµ� ��츸 ó��
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
	// enter �Է��ΰ�츸 ó��
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


	// �Է� ����
	InputText.Empty();
}
