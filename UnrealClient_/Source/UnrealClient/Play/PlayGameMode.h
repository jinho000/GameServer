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
	// OtherCharacter�� �����ϱ� ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClientData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AClientCharacter> OtherPlayerClass;

private:
	// OtherCharacter�� ó���ϱ����� �����̳�
	TMap<uint64_t, AActor*> m_allOtherCharacter;

public:
	FORCEINLINE TSubclassOf<AClientCharacter> GetOtherPlayerClass()
	{
		return OtherPlayerClass;
	}

	void SpawnNewOtherPlayer(uint64_t _playerID);

};
