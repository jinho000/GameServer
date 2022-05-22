// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacter.h"

// Sets default values
AClientCharacter::AClientCharacter()
	: m_AnimationInst(nullptr)
	, m_playerID(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClientCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimationInst = Cast<UClientAnimInstance>(GetMesh()->GetAnimInstance());
	m_AnimationInst->SetAnimationMap(&m_Animations);
	m_AnimationInst->ChangeAnimation(ClientAnimationType::Idle);
}

// Called every frame
void AClientCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AClientCharacter::LookZ(FVector _Dir, float _Ratio)
{
	// 캐릭터가 바라봐야하는 dir
	FVector LookVector = _Dir.GetSafeNormal();
	FVector CurVector = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).Vector().GetSafeNormal();

	FVector CorssVector = FVector::CrossProduct(CurVector, LookVector);
	float DotValue = FVector::DotProduct(CurVector, LookVector);

	float ACos = FMath::Acos(DotValue);

	if (CorssVector.Z < 0)
	{
		ACos *= -1.0f;
	}

	return FMath::RadiansToDegrees(ACos) * _Ratio;
}

