// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PacketComponent.generated.h"

//패킷을 메시지 컴포넌트에서 매프레임마다 틱을 돌며 큐에있는 패킷을 처리
//게임모드에 메시지컴포넌트를 추가
//(패킷을 틱마다 확인하여 처리해야하기 때문,
//	게임인스턴스에는 틱함수가 없음
//	각 게임모드마다 메시지 컴포넌트를 추가하여 틱마다 처리
//	게임모드의 틱은 매틱마다 처음으로 실행
//)
// 
// 리시브 패킷을 처리하기 위한 패킷 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCLIENT_API UPacketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPacketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
