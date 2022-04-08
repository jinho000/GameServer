// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CChatMessage.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCChatMessage : public UObject
{
	GENERATED_BODY()

private:
	FString m_chatMessage;

public:
	void Init(const FString& _nickName, const FString& _message);
	const FString& GetChatMessage() const;
};
