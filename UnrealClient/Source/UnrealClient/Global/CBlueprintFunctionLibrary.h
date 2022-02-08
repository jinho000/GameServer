// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <string>

#include "CBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UCBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void FStringToUTF8(const FString& _fString, std::string& _outUTF8String);
	static void UTF8ToFString(const std::string& _UTF8String, FString& _outFString);
};
