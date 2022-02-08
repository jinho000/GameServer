// Fill out your copyright notice in the Description page of Project Settings.

#include "CBlueprintFunctionLibrary.h"
#include <Containers/StringConv.h>

void UCBlueprintFunctionLibrary::FStringToUTF8(const FString& _fString, std::string& _outUTF8String)
{
	FTCHARToUTF8 convert(*_fString);
	_outUTF8String = std::string(convert.Get());
}


void UCBlueprintFunctionLibrary::UTF8ToFString(const std::string& _UTF8String, FString& _outFString)
{
	FUTF8ToTCHAR convert(_UTF8String.c_str());
	_outFString = FString(convert.Get());
}
