// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterListItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCharacterListItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharcterListItem")
	FString NickName;

	UFUNCTION(BlueprintCallable, Category = "CharcterListItem")
	void SelectCharacter();

	UFUNCTION(BlueprintCallable, Category = "CharcterListItem")
	void CreateCharacter();

	UFUNCTION(BlueprintCallable, Category = "CharcterListItem")
	void DeleteCharacter();

private:
	void Toggle(bool _hide);

public:
	void HideItem();
	void ShowItem();

};
