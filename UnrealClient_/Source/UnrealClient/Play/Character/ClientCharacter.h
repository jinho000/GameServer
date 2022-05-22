// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ClientAnimInstance.h"
#include "ClientAnimEnums.h"
#include "ClientCharacter.generated.h"

UCLASS()
class UNREALCLIENT_API AClientCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClientData", meta = (AllowPrivateAccess = "true"))
	TMap <ClientAnimationType, class UAnimMontage* >	m_Animations;

	UClientAnimInstance*								m_AnimationInst;

	uint64_t											m_playerID;

public:
	// Sets default values for this character's properties
	AClientCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	FORCEINLINE UClientAnimInstance* GetClientAnimInstance()
	{
		return m_AnimationInst;
	}


	float LookZ(FVector _Dir, float _Ratio = 1.0f);

	void SetPlayerID(uint64_t _playerID)
	{
		m_playerID = _playerID;
	}

	uint64_t GetPlayerID() { return m_playerID; }
};
