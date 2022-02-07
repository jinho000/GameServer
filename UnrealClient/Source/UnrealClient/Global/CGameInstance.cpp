// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"
#include <Sockets.h>
#include <SocketSubsystem.h>
#include <Interfaces/IPv4/IPv4Address.h>
#include <Interfaces/IPv4/IPv4Endpoint.h>


UCGameInstance::UCGameInstance()
	: m_socketSystem(nullptr)
	, m_socket(nullptr)
{
	int a = 0;
}

UCGameInstance::~UCGameInstance()
{
	int a = 0;
}

void UCGameInstance::CloseSocket()
{
	if (nullptr == m_socket)
	{
		return;
	}

	m_socket->Close();
	m_socket = nullptr;
}

bool UCGameInstance::ConnectServer(const FString& _IP, const FString& _port)
{
	// 소켓 정리
	CloseSocket();

	// 소켓 만들기
	m_socketSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	FString socketDesc = TEXT("Socket Description");
	m_socket = m_socketSystem->CreateSocket(NAME_Stream, socketDesc, false);
	if (nullptr == m_socket)
	{
		// 소켓 생성 실패
		UE_LOG(LogTemp, Error, TEXT("Create Socket Error"));
		return false;
	}

	// 소켓 옵션 설정
	m_socket->SetNoDelay();

	// 소켓 연결
	// 소켓 EndPoint 만들기
	FIPv4Address connectAddr;
	FIPv4Address::Parse(_IP, connectAddr);
	uint16 port = static_cast<uint16>(FCString::Atoi(*_port));
	FIPv4Endpoint endPoint(connectAddr, port);

	if (false == m_socket->Connect(endPoint.ToInternetAddr().Get()))
	{
		// 접속 실패
		FString error = m_socketSystem->GetSocketError(m_socketSystem->GetLastErrorCode());
		UE_LOG(LogTemp, Error, TEXT("GameInstance - %s"), *error);

		CloseSocket();
		return false;
	}


	// 스레드 만들어 Recv데이터 받기

	return true;
}
