// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientCharacter.h"
#include "ClientPlayCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API AClientPlayCharacter : public AClientCharacter
{
	GENERATED_BODY()

private:
	FVector		m_MoveVector;

	float		m_pingTime; // ping 체크용 시간

public:
	// Sets default values for this character's properties
	AClientPlayCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float _Rate);
	void MoveRight(float _Rate);
	void MoveStart();
	void MoveEnd();

	void Attack();

	void SendUDPPlayerData();

	// _Dir방향으로 캐릭터가 바라봄
	FVector MouseVectorToWorldVector();

	// 기능 테스트 함수
	void TestFunction();

public:
	void PingStart();
	void PingEnd();
};
