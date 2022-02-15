// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include <memory>

#include "../Global/CGameInstance.h"
#include "Components/ActorComponent.h"
#include "ClientPackets/ClientPacketBase.h"
#include "PacketComponent.generated.h"

using ClientPacketHandler = std::function<void(std::shared_ptr<ClientPacketBase>)>;

//��Ŷ�� �޽��� ������Ʈ���� �������Ӹ��� ƽ�� ���� ť���ִ� ��Ŷ�� ó��
//���Ӹ�忡 �޽���������Ʈ�� �߰�
//(��Ŷ�� ƽ���� Ȯ���Ͽ� ó���ؾ��ϱ� ����,
//	�����ν��Ͻ����� ƽ�Լ��� ����
//	�� ���Ӹ�帶�� �޽��� ������Ʈ�� �߰��Ͽ� ƽ���� ó��
//	���Ӹ���� ƽ�� ��ƽ���� ó������ ����
//)
// 
// ���ú� ��Ŷ�� ó���ϱ� ���� ��Ŷ ������Ʈ
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCLIENT_API UPacketComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TMap<PacketType, ClientPacketHandler> m_handlerContainer;
	UCGameInstance* m_pGameInst;
	
public:	
	// Sets default values for this component's properties
	UPacketComponent();

private:
	//const PacketHandler& GetHandler(PacketType _type);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
