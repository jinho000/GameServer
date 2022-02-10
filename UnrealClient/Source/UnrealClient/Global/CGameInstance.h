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
// ���� ���ۺ��� ����ñ��� ����ִ� Ŭ����
// ������ �ٲ𶧿��� ���� ������ ó��
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
	// ���� ���� �Լ�
	bool ConnectServer(const FString& _IP, const FString& _port);

	bool SendBytes(const std::vector<uint8>& _bytes);

	// ����� ������ ������ ���� �Լ�(�𸮾��� ���ڿ����� UTF16)
	// ������ Ŭ���̾�Ʈ�� ���ڿ� ������ �ٸ��� ������ �ϳ��� �����ؾ���
	// -> UTF8 �������� ����
	//    ���۽� utf8�� ��ȯ�Ͽ� ����, ���Ž� utf8�� ��ȯ�Ͽ� ����
	bool SendFString(const FString& _fstr);
};
