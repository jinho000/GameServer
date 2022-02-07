// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

/**
 * 
 */
// ���� ���ۺ��� ����ñ��� ����ִ� Ŭ����
// ������ �ٲ𶧿��� ���� ������ ó��
UCLASS()
class UNREALCLIENT_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	ISocketSubsystem*	m_socketSystem;
	FSocket*			m_socket;

public:
	UCGameInstance();
	virtual ~UCGameInstance();

private:
	void CloseSocket();


public:
	bool ConnectServer(const FString& _IP, const FString& _port);


};
