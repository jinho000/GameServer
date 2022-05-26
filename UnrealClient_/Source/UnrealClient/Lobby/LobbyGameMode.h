// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	uint64_t m_playerID;

public:
	virtual void BeginPlay() override;

public:
	void SetPlayerID(uint64_t playerID);
	uint64_t GetPlayerID();
};
