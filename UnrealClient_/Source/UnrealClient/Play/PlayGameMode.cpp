// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "../Global/CGameInstance.h"
#include "Character/ClientOtherCharacter.h"


void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 다른 플레이어 생성
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	SpawnOtherPlayer(gameInst->GetOtherPlayerID());
}

void APlayGameMode::SpawnOtherPlayer(const std::vector<uint64_t>& arryOtherPlayerID)
{
	FTransform Transform = { };

	UWorld* pWorld = GetWorld();

	for (size_t i = 0; i < arryOtherPlayerID.size(); i++)
	{
		AClientCharacter* otherCharacter = pWorld->SpawnActorDeferred<AClientCharacter>(OtherPlayerClass.Get(), Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		otherCharacter->FinishSpawning(Transform);
		otherCharacter->SetPlayerID(arryOtherPlayerID[i]);

		// spwan된 캐릭터 위치 설정
		//FVector4 Rot = _playerData.Rot;
		//FQuat RotData = FQuat(Rot.X, Rot.Y, Rot.Z, Rot.W);
		//otherCharacter->SetActorRotation(RotData);
		otherCharacter->SetActorLocation(FVector4(0.f, 0.f, 800.f));

		m_allOtherCharacter.Add(arryOtherPlayerID[i], otherCharacter);
	}

}

void APlayGameMode::UpdateOtherPlayerInfo(const std::vector<FPlayerUpdateData>& _allPlayerInfo)
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	for (const FPlayerUpdateData& playerData : _allPlayerInfo)
	{
		if (playerData.PlayerID == gameInst->GetPlayerID())
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

