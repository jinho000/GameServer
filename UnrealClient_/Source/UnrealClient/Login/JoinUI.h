// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UJoinUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoinInfo")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoinInfo")
	FString Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoinInfo")
	FString JoinState;

public:
	void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "JoinInfo")
	bool Join();
};
