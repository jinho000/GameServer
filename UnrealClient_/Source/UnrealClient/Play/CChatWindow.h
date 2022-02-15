// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"

#include "CChatWindow.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCChatWindow : public UUserWidget
{
	GENERATED_BODY()

public: 
	// ������ ���� ���� (���������� = �����̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UListView* MessageList;

public:
	UFUNCTION(BlueprintCallable, Category = "Chatting")
	void AddChatMessage(UObject* _chatMsgObj, UUserWidget* _chatMsgWidget);

	UFUNCTION(BlueprintCallable, Category = "Chatting")
	void OnChatMsgCommitted(const FString& _text, ETextCommit::Type _textType);
};
