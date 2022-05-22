// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayGameMode.h"
#include <Kismet/GameplayStatics.h>

void APlayGameMode::SpawnNewOtherPlayer(uint64_t _playerID)
{
	if (nullptr != m_allOtherCharacter.Find(_playerID))
	{
		// 이미 스폰된 플레이어임
		UE_LOG(LogTemp, Log, TEXT("Already Spawned Player"));
		return;
	}

	FTransform Transform = { };
	Transform.SetLocation({ 0, 0, 400.f });

	UWorld* pWorld = GetWorld();
	AClientCharacter* otherCharacter = pWorld->SpawnActorDeferred<AClientCharacter>(OtherPlayerClass.Get(), Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	otherCharacter->FinishSpawning(Transform);
	otherCharacter->SetPlayerID(_playerID);

	m_allOtherCharacter.Add(_playerID, otherCharacter);
}
