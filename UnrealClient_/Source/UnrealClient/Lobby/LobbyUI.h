// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API ULobbyUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UFUNCTION: 블루프린트에서 함수를 사용하기 위한 설정
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void RequestGameMatch();

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void Cancel();
};
