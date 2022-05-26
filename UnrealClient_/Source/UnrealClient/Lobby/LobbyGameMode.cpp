// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "../Global/CGameInstance.h"
#include "../Packets/ClientPackets/Packets.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 레벨 진입시, 플레이어 생성시 UDP소켓 생성 
	// UPD 통신 처리를 위한 스레드는 플레이모드에서 시작
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	gameInst->ConnectUDPServer();

	// 플레이어 처음 위치와 포트를 서버에 TCP로 전송
	UDPStartPacket packet;
	packet.udpPort = gameInst->GetUnrealUDPPort();

	ServerSerializer sr;
	packet >> sr;
	gameInst->SendBytes(sr.GetBuffer());
}

