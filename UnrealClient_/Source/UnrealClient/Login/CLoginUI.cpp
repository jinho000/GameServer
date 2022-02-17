// Fill out your copyright notice in the Description page of Project Settings.


#include "CLoginUI.h"
#include <vector>
#include "../Global/CGameInstance.h"
#include "../Packets/ClientPackets/LoginPacket.h"
#include "../Packets/ClientSerializer.h"


void UCLoginUI::ResetConnectInfo()
{
	IP = TEXT("127.0.0.1");
	Port = TEXT("30001");
}

bool UCLoginUI::ConnectServer()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	return gameInst->ConnectServer(IP, Port);
}

bool UCLoginUI::Login()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	gameInst->SetUserID(ID);
	UE_LOG(LogTemp, Log, TEXT("Login user id: %s"), *ID);
	

	// 서버에 유저 정보 전달
	LoginPacket packet(ID, Password);
	ClientSerializer sr;
	packet >> sr;
	
	return gameInst->SendBytes(sr.GetBuffer());
}
