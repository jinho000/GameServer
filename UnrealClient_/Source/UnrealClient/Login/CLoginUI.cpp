// Fill out your copyright notice in the Description page of Project Settings.


#include "CLoginUI.h"
#include <vector>
#include "../Global/CGameInstance.h"
#include "../Packets/ClientPackets/ServerAndClient.h"
#include "../Packets/ClientPackets/ServerToClient.h"
#include "../Packets/ClientPackets/ClientToServer.h"
#include "../Packets/ClientPackets/ServerSerializer.h"
#include "JoinUI.h"

void UCLoginUI::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	UCGameInstance* Inst = Cast<UCGameInstance>(GetGameInstance());
	Inst->LoginUI = this;
}

void UCLoginUI::ResetConnectInfo()
{
	IP = TEXT("127.0.0.1");
	Port = TEXT("30001");
}

bool UCLoginUI::ConnectServer()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	gameInst->ConnectServer(IP, Port);

	return true;
}

bool UCLoginUI::Login()
{
	UE_LOG(LogTemp, Log, TEXT("Login user id: %s"), *ID);
	UE_LOG(LogTemp, Log, TEXT("Login user pw: %s"), *Password);
	

	// 서버에 유저 정보 전달
	LoginPacket packet;
	packet.ID = std::string(FTCHARToUTF8(*ID).Get());
	packet.PW = std::string(FTCHARToUTF8(*Password).Get());

	ServerSerializer sr;
	packet >> sr;
	
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	return gameInst->SendBytes(sr.GetBuffer());
}

void UCLoginUI::PressJoinBtn()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	gameInst->JoinUI->JoinState = FString();
	gameInst->JoinUI->ID = FString();
	gameInst->JoinUI->Password = FString();
}
