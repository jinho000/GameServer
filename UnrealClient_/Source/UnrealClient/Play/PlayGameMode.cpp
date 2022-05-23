// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayGameMode.h"
#include <Kismet/GameplayStatics.h>

void APlayGameMode::SpawnOtherPlayer(const FPlayerUpdateData& _playerData)
{
	if (nullptr != m_allOtherCharacter.Find(_playerData.PlayerID))
	{
		// �̹� ������ �÷��̾���
		UE_LOG(LogTemp, Log, TEXT("Already Spawned Player"));
		return;
	}

	FTransform Transform = { };

	UWorld* pWorld = GetWorld();
	AClientCharacter* otherCharacter = pWorld->SpawnActorDeferred<AClientCharacter>(OtherPlayerClass.Get(), Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	otherCharacter->FinishSpawning(Transform);
	otherCharacter->SetPlayerID(_playerData.PlayerID);

	// spwan�� ĳ���� ��ġ ����
	FVector4 Rot = _playerData.Rot;
	FQuat RotData = FQuat(Rot.X, Rot.Y, Rot.Z, Rot.W);
	otherCharacter->SetActorRotation(RotData);
	otherCharacter->SetActorLocation(_playerData.Pos);

	m_allOtherCharacter.Add(_playerData.PlayerID, otherCharacter);
}
