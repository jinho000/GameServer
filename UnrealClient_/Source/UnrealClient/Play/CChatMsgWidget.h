// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CChatMsgWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCChatMsgWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChatMessage")
	FString Message;

};
