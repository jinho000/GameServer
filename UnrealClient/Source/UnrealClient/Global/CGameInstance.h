// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include <vector>
#include <memory>

#include "../Packets/ClientPacketBase.h"
#include "UnrealThread.h"
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
	TQueue<std::shared_ptr<ClientPacketBase>> m_packetQueue;

	UnrealThread*		m_recvThread;
	FRunnableThread*	m_runnableThread;

	ISocketSubsystem*	m_socketSystem;
	FSocket*			m_socket;

public:
	UCGameInstance();
	virtual ~UCGameInstance();

private:
	void CloseSocket();


public:
	// 서버 연결 함수
	bool ConnectServer(const FString& _IP, const FString& _port);

	bool SendBytes(const std::vector<uint8>& _bytes);

	// 연결된 서버에 데이터 전송 함수(언리얼의 문자열셋은 UTF16)
	// 서버와 클라이언트의 문자열 세팅이 다르기 때문에 하나로 통일해야함
	// -> UTF8 형식으로 통일
	//    전송시 utf8로 변환하여 전송, 수신시 utf8을 변환하여 수신
	bool SendFString(const FString& _fstr);
};
