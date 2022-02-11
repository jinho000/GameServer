// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PacketComponent.generated.h"

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
