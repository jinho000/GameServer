// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

/**
 * 
 */
// 게임 시작부터 종료시까지 살아있는 클래스
// 레벨이 바뀔때에도 남아 할일을 처리
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
