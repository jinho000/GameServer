// Fill out your copyright notice in the Description page of Project Settings.


#include "CLoginUI.h"
#include <vector>
#include "../Global/CGameInstance.h"


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
	return gameInst->SendFString(IP);


}
