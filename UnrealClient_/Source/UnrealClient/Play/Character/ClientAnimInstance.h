// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ClientAnimEnums.h"
#include "ClientAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UClientAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	ClientAnimationType							m_currentAnimationType;
	TMap <ClientAnimationType, UAnimMontage* >* m_animations;

public:
	UClientAnimInstance();

protected:
	void NativeUpdateAnimation(float _DeltaTime);

	UFUNCTION()
	void AnimNotify_End();

public:
	FORCEINLINE void SetAnimationMap(TMap <ClientAnimationType, UAnimMontage* >* _Map)
	{
		m_animations = _Map;
	}

	FORCEINLINE ClientAnimationType GetAnimationType()
	{
		return m_currentAnimationType;
	}

	void ChangeAnimation(ClientAnimationType _Type);

	bool IsCanMove();
};
