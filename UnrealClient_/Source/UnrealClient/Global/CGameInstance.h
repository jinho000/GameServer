// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include <vector>
#include <memory>

#include "../Packets/ClientPackets/ClientPacketBase.h"
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
	// Socket
	TQueue<std::shared_ptr<ClientPacketBase>> m_packetQueue;

	UnrealThread*		m_recvThread;
	FRunnableThread*	m_runnableThread;

	ISocketSubsystem*	m_socketSystem;
	FSocket*			m_socket;

	// UserInfo
	FString				m_userID;

public:
	UCGameInstance();
	virtual ~UCGameInstance();

// Socket
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

	TQueue<std::shared_ptr<ClientPacketBase>>& GetPacketQueue() { return m_packetQueue; }

// UserInfo
public:
	const FString& GetUserID() { return m_userID; }
	void SetUserID(const FString& _id) { m_userID = _id; }
};
