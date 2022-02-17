// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketComponent.h"
#include "ClientPackets/LoginResultPacket.h"
#include "PacketHandler/HandlerHeader.h"

// 패킷 처리 함수
//void ProcessHandler(std::shared_ptr<ClientPacketBase> _packet, UCGameInstance* _instance, UWorld* _world)
//{
//
//}

template<class HandlerClass, class PacketClass>
void ProcessHandler(std::shared_ptr<ClientPacketBase> _packet, UCGameInstance* _instance, UWorld* _world)
{
	std::shared_ptr<PacketClass> packet = std::static_pointer_cast<PacketClass>(_packet);
	if (nullptr == packet)
	{
		UE_LOG(LogTemp, Error, TEXT("packet nullptr"));
		return;
	}

	HandlerClass handler(packet);
	handler.Init(_instance, _world);
	handler.Start();
}


// Sets default values for this component's properties
UPacketComponent::UPacketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	m_pGameInst = nullptr;
}

// Called when the game starts
void UPacketComponent::BeginPlay()
{
	Super::BeginPlay();

	// 여기서 처리할 핸들러 추가
	UE_LOG(LogTemp, Log, TEXT("Packet Component Begin Play"));

	m_pGameInst = Cast<UCGameInstance>(GetOwner()->GetGameInstance());
	UWorld* world = GetWorld();

	m_handlerContainer.Add(PacketType::LOGIN_RESULT
		, std::bind(&ProcessHandler<LoginResultPacketHandler, LoginResultPacket>, std::placeholders::_1, m_pGameInst, world));

}


// Called every frame
void UPacketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 리시브 큐에 있는 패킷을 모두 꺼내 핸들러로 처리
	TQueue<std::shared_ptr<ClientPacketBase>>& packetQueue = m_pGameInst->GetPacketQueue();
	
	while (false == packetQueue.IsEmpty())
	{
		std::shared_ptr<ClientPacketBase> packet;
		packetQueue.Dequeue(packet);
		PacketType type = packet->GetPacketType();
		ClientPacketHandler* handler = m_handlerContainer.Find(packet->GetPacketType());
		
		if (nullptr == handler)
		{
			UE_LOG(LogTemp, Log, TEXT("packet handler is nullptr"));
			continue;
		}

		(*handler)(packet);
	}
}

