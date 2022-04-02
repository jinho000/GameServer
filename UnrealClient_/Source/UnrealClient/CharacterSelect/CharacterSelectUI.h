// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCharacterSelectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharaterSelectUI")
	FString NickName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharaterSelectUI")
	class UListView* CharacterListView;

public:
	void NativeConstruct() override;

public: // 블루프린트에서 사용할 함수

	// UFUNCTION: 블루프린트에서 함수를 사용하기 위한 설정
	UFUNCTION(BlueprintCallable, Category = "CharaterSelectUI")
	void CreateCharacter();

	UFUNCTION(BlueprintCallable, Category = "CharaterSelectUI")
	void AddItemToListEvent(UObject* _Object, UUserWidget* _Widget);
};
