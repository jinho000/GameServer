// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketComponent.h"

// Sets default values for this component's properties
UPacketComponent::UPacketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPacketComponent::BeginPlay()
{
	Super::BeginPlay();

	// 여기서 처리할 핸들러 추가
	UE_LOG(LogTemp, Log, TEXT("Packet Component Begin Play"));
	
}


// Called every frame
void UPacketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 리시브 큐에 있는 패킷을 모두 꺼내 핸들러로 처리

}

