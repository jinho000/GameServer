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

	// ���⼭ ó���� �ڵ鷯 �߰�
	UE_LOG(LogTemp, Log, TEXT("Packet Component Begin Play"));
	
}


// Called every frame
void UPacketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���ú� ť�� �ִ� ��Ŷ�� ��� ���� �ڵ鷯�� ó��

}

