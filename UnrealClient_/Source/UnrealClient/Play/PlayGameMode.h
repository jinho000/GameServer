// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Character/ClientCharacter.h"
#include "Character/ClientPlayCharacter.h"
#include "../Packets/ClientPackets/ContentStruct.h"
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

	AClientPlayCharacter*	m_player;

public:
	FORCEINLINE TSubclassOf<AClientCharacter> GetOtherPlayerClass()
	{
		return OtherPlayerClass;
	}

public:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;


public:
	void SetPlayer(AClientPlayCharacter* _player) { m_player = _player; }
	AClientPlayCharacter* GetPlayer() { return m_player; }

	void SpawnOtherPlayer(const FPlayerUpdateData& _playerData);
	void UpdateOtherPlayerInfo(const std::vector<FPlayerUpdateData>& _allPlayerInfo);
};
