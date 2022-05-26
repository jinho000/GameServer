// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyUI.h"
#include <Kismet/GameplayStatics.h>
#include "../Lobby/LobbyGameMode.h"
#include "../Global/CGameInstance.h"
#include "../Packets/ClientPackets/Packets.h"

void ULobbyUI::RequestGameMatch()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	ALobbyGameMode* pLobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	// ��Ī ��û ��Ŷ ������
	RequestMathPacket packet;
	packet.PlayerID = pLobbyGameMode->GetPlayerID();
	ServerSerializer sr;
	packet >> sr;
	gameInst->SendBytes(sr.GetBuffer());
}

void ULobbyUI::Cancel()
{
}
