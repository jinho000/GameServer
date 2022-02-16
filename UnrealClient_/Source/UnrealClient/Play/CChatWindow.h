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
	// 변수에 위젯 세팅 (위젯변수명 = 위젯이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UListView* MessageList;

	// 입력 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chatting")
	FString InputText;

public:
	UFUNCTION(BlueprintCallable, Category = "Chatting")
	void AddChatMessage(UObject* _chatMsgObj, UUserWidget* _chatMsgWidget);

	UFUNCTION(BlueprintCallable, Category = "Chatting")
	void OnChatMsgCommitted(const FString& _text, ETextCommit::Type _commitType);
};
