// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientAnimInstance.h"
#include "../../UnrealClient.h"

UClientAnimInstance::UClientAnimInstance()
	: m_currentAnimationType(ClientAnimationType::NONE)
	, m_animations(nullptr)
{

}

void UClientAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	if (nullptr == m_animations)
	{
		return;
	}

	Super::NativeUpdateAnimation(_DeltaTime);

	if (false == (*m_animations).Contains(m_currentAnimationType))
	{
		return;
	}

	UAnimMontage* FindAnimation = (*m_animations)[m_currentAnimationType];

	if (nullptr == FindAnimation)
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Animation Is Null"), __FUNCTION__, __LINE__);
	}

	if (true == Montage_IsPlaying(FindAnimation))
	{
		return;
	}

	Montage_Play(FindAnimation);
}

void UClientAnimInstance::ChangeAnimation(ClientAnimationType _Type) {
	m_currentAnimationType = _Type;
}


bool UClientAnimInstance::IsCanMove()
{
	return m_currentAnimationType != ClientAnimationType::Attack;
}


void UClientAnimInstance::AnimNotify_End()
{
	m_currentAnimationType = ClientAnimationType::Idle;
}