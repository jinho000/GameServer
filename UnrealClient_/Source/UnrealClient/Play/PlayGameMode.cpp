// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "../Global/CGameInstance.h"
#include "Character/ClientOtherCharacter.h"

void APlayGameMode::StartPlay()
{
	Super::StartPlay();

}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ���⼭ UDP ���� �ʱ�ȭ
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	gameInst->ConnectUDPServer();

}

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

void APlayGameMode::UpdateOtherPlayerInfo(const std::vector<FPlayerUpdateData>& _allPlayerInfo)
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	for (const FPlayerUpdateData& playerData : _allPlayerInfo)
	{
		if (playerData.PlayerID == m_player->GetPlayerID())
		{
			continue;
		}

		AClientOtherCharacter* pOtherCharacter = Cast<AClientOtherCharacter>(*(m_allOtherCharacter.Find(playerData.PlayerID)));
		
		pOtherCharacter->GetClientAnimInstance()->ChangeAnimation(static_cast<ClientAnimationType>(playerData.State));

		FVector4 Rot = playerData.Rot;
		FQuat RotData = FQuat(Rot.X, Rot.Y, Rot.Z, Rot.W);
		pOtherCharacter->SetActorRotation(RotData);
		pOtherCharacter->SetActorLocation(playerData.Pos);
	}
}

