// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterListItem.h"

void UCharacterListItem::SelectCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Select Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);
}
