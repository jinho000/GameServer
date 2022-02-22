// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPlayCharacter.h"
#include <GameFramework/PlayerInput.h>
#include "../../UnrealClient.h"

AClientPlayCharacter::AClientPlayCharacter()
	: AClientCharacter()
	, m_MoveVector()
{
}

// Called when the game starts or when spawned
void AClientPlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClientPlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClientPlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 키, 함수 바인딩은 한번만 처리
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// 얼마나 지속적으로 오래눌렀고 세게 눌렀다 약하게 눌렀다는 체크해야할때가 많습니다.
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ClientPlayer_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ClientPlayer_MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::W));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::S));


		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ClientPlayer_MoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ClientPlayer_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::D));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::A));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Attack", EKeys::LeftMouseButton));
	}

	// 정의 내린 키가 입력되었을대 
	PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &AClientPlayCharacter::MoveForward);
	PlayerInputComponent->BindAxis("ClientPlayer_MoveRight", this, &AClientPlayCharacter::MoveRight);
	PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Pressed, this, &AClientPlayCharacter::MoveStart);
	PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Released, this, &AClientPlayCharacter::MoveEnd);

	PlayerInputComponent->BindAction("ClientPlayer_Attack", EInputEvent::IE_Released, this, &AClientPlayCharacter::Attack);

	// 마우스 설정?
	//FInputModeGameAndUI InputMode;
	//GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
	//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void AClientPlayCharacter::LookZ(FVector _Dir, float _Ratio /*= 1.0f*/)
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

	AddControllerYawInput(FMath::RadiansToDegrees(ACos) * _Ratio);
}

void AClientPlayCharacter::MoveRight(float _Rate)
{
	if (false == GetClientAnimInstance()->IsCanMove())
	{
		return;
	}

	if (0.0f == _Rate)
	{
		return;
	}

	LookZ(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f);

	AddMovementInput(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal(), _Rate);
	GetClientAnimInstance()->ChangeAnimation(ClientAnimationType::Move);
}

void AClientPlayCharacter::MoveForward(float _Rate)
{
	if (false == GetClientAnimInstance()->IsCanMove())
	{
		return;
	}

	if (0.0f == _Rate)
	{
		return;
	}

	LookZ(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f);

	AddMovementInput(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal(), _Rate);
	GetClientAnimInstance()->ChangeAnimation(ClientAnimationType::Move);
}

void AClientPlayCharacter::MoveStart()
{
	if (false == GetClientAnimInstance()->IsCanMove())
	{
		return;
	}

	GetClientAnimInstance()->ChangeAnimation(ClientAnimationType::Move);
}

void AClientPlayCharacter::MoveEnd()
{
	if (false == GetClientAnimInstance()->IsCanMove())
	{
		return;
	}


	GetClientAnimInstance()->ChangeAnimation(ClientAnimationType::Idle);
}

void AClientPlayCharacter::Attack()
{
	// 화면을 바라보는건 클라이언트 뿐입니다.

	// LookZ(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f);

	LookZ(MouseVectorToWorldVector() - GetActorLocation());

	GetClientAnimInstance()->ChangeAnimation(ClientAnimationType::Attack);
}


FVector AClientPlayCharacter::MouseVectorToWorldVector()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (nullptr == PC && PC->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > nullptr Controller"), __FUNCTION__, __LINE__);
		// 정한거다. 
		return FVector(TNumericLimits<float>::Max(), TNumericLimits<float>::Max(), TNumericLimits<float>::Max());
	}

	FHitResult TraceHitResult;

	if (false == PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult))
	{
		//     월드 좌표이기 때문에
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > GetHitResultUnderCursor false"), __FUNCTION__, __LINE__);
		return FVector(TNumericLimits<float>::Max(), TNumericLimits<float>::Max(), TNumericLimits<float>::Max());
	}

	return TraceHitResult.Location;
}