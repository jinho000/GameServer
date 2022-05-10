// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include <vector>
#include <memory>
#include <Interfaces/IPv4/IPv4Endpoint.h>

#include "../Packets/ClientPackets/ServerPacketBase.h"
#include "UnrealThread.h"
#include "CGameInstance.generated.h"

class UCChatWindow;


// 게임 시작부터 종료시까지 살아있는 클래스
// 레벨이 바뀔때에도 남아 할일을 처리
UCLASS()
class UNREALCLIENT_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	// Socket
	TQueue<std::shared_ptr<ServerPacketBase>> m_packetQueue;

	UnrealThread*		m_recvThread;
	FRunnableThread*	m_runnableThread;

	ISocketSubsystem*	m_socketSystem;
	FSocket*			m_socket;
	FSocket*			m_UDPsocket;

	// Server Info
	FString				m_serverIP;			// TCP, UDP 같은서버 사용
	uint16				m_TCPServerPort;

	uint16				m_UDPServerPort;
	uint16				m_unrealUDPPort;	

	FIPv4Endpoint		m_serverUDPEndPoint;

	// Chatting
	UCChatWindow*		m_chatWindow;

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
	// 서버 연결 함수
	bool ConnectServer(const FString& _IP, const FString& _port);
	bool ConnectUDPServer(uint64 _serverUDPPort);

	bool SendBytes(const std::vector<uint8>& _packet);

	// 연결된 서버에 데이터 전송 함수(언리얼의 문자열셋은 UTF16)
	// 서버와 클라이언트의 문자열 세팅이 다르기 때문에 하나로 통일해야함
	// -> UTF8 형식으로 통일
	//    전송시 utf8로 변환하여 전송, 수신시 utf8을 변환하여 수신
	//bool SendFString(const FString& _fstr);

	TQueue<std::shared_ptr<ServerPacketBase>>& GetPacketQueue() { return m_packetQueue; }

	// Server Packet 테스트함수
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
