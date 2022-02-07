// Fill out your copyright notice in the Description page of Project Settings.


#include "CLoginUI.h"
#include "../Global/CGameInstance.h"

void UCLoginUI::ResetConnectInfo()
{
	IP = TEXT("127.0.0.1");
	Port = TEXT("30001");
}

void UCLoginUI::ConnectServer()
{
	UCGameInstance* gameInst = Cast<UCGameInstance>(GetGameInstance());
	if (nullptr == gameInst)
	{
		return;
	}

	if (false == gameInst->ConnectServer(IP, Port))
	{

		return;
	}
}

void UCLoginUI::Login()
{
	int a = 0;
}
