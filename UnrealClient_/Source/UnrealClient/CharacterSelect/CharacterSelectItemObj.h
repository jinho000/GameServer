// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <string>
#include "CharacterSelectItemObj.generated.h"

struct FCharacterInfo
{
	std::string nickName;
};

UCLASS()
class UNREALCLIENT_API UCharacterSelectItemObj : public UObject
{
	GENERATED_BODY()
	
public:
	FCharacterInfo CharacterInfo;
};
