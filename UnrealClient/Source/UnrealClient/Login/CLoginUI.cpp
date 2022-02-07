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

	// UTF16 
	//const char* utf8 = TCHAR_TO_UTF8(*IP);
	//
	//std::vector<uint8> vecBytes;
	//vecBytes.reserve(100);
	//while ('\0' != *utf8)
	//{
	//	vecBytes.push_back(*utf8);
	//	++utf8;
	//}

	//vecBytes.push_back('\0');

	//FString recv(UTF8_TO_TCHAR(vecBytes.data()));
	//gameInst->SendBytes(vecBytes);
}
