// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Character/ClientCharacter.h"
#include "PlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API APlayGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	// OtherCharacter를 생성하기 위한 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClientData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AClientCharacter> OtherPlayerClass;

private:
	// OtherCharacter를 처리하기위한 컨테이너
	TMap<uint64_t, AActor*> m_allOtherCharacter;

public:
	FORCEINLINE TSubclassOf<AClientCharacter> GetOtherPlayerClass()
	{
		return OtherPlayerClass;
	}

	void SpawnNewOtherPlayer(uint64_t _playerID);

};
