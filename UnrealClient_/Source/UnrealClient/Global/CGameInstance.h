// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include <vector>
#include <memory>

#include "../Packets/ClientPackets/ServerPacketBase.h"
#include "UnrealThread.h"
#include "CGameInstance.generated.h"

class UCChatWindow;


// ���� ���ۺ��� ����ñ��� ����ִ� Ŭ����
// ������ �ٲ𶧿��� ���� ������ ó��
UCLASS()
class UNREALCLIENT_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	// Socket
	TQueue<std::shared_ptr<ServerPacketBase>> m_packetQueue;

	UnrealThread* m_recvThread;
	FRunnableThread* m_runnableThread;

	ISocketSubsystem* m_socketSystem;
	FSocket* m_socket;

	// Chatting
	UCChatWindow*	m_chatWindow;

public:
	// Login
	TAtomic<bool>		LoginProcess;
	class UCLoginUI*	LoginUI;

	// Join
	class UJoinUI*		JoinUI;

	// User
	std::vector<FCharacterInfo> UserCharacterList;
	FCharacterInfo				SelectCharacter;

	// Chracter Select UI
	class UCharacterSelectUI*	CharacterSelectUI;
	class UListView*			CharacterSelectUIListView;

// default
public:
	UCGameInstance();
	virtual ~UCGameInstance();

// Socket
private:
	void CloseSocket();


// Server
public:
	// ���� ���� �Լ�
	bool ConnectServer(const FString& _IP, const FString& _port);

	bool SendBytes(const std::vector<uint8>& _packet);

	// ����� ������ ������ ���� �Լ�(�𸮾��� ���ڿ����� UTF16)
	// ������ Ŭ���̾�Ʈ�� ���ڿ� ������ �ٸ��� ������ �ϳ��� �����ؾ���
	// -> UTF8 �������� ����
	//    ���۽� utf8�� ��ȯ�Ͽ� ����, ���Ž� utf8�� ��ȯ�Ͽ� ����
	//bool SendFString(const FString& _fstr);

	TQueue<std::shared_ptr<ServerPacketBase>>& GetPacketQueue() { return m_packetQueue; }

	// Server Packet �׽�Ʈ�Լ�
	void AddServerPacket(std::shared_ptr<ServerPacketBase> _serverPacket);

// Chatting
public:

	UCChatWindow* GetChatWindow() 
	{
		check(nullptr != m_chatWindow)
		return m_chatWindow; 
	}

	void SetChatWindow(UCChatWindow* _chatWindow) { m_chatWindow = _chatWindow; }

// Characte
public:
	void DeleteCharacter(const std::string& _deleteNickName);
};
