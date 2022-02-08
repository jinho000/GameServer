// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"
#include <Sockets.h>
#include <SocketSubsystem.h>
#include <Interfaces/IPv4/IPv4Address.h>
#include <Interfaces/IPv4/IPv4Endpoint.h>

#include "CBlueprintFunctionLibrary.h"

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
	// ���� ����
	CloseSocket();

	// ���� �����
	m_socketSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	FString socketDesc = TEXT("Socket Description");
	m_socket = m_socketSystem->CreateSocket(NAME_Stream, socketDesc, false);
	if (nullptr == m_socket)
	{
		// ���� ���� ����
		UE_LOG(LogTemp, Error, TEXT("GameInstance - Create Socket Error"));
		return false;
	}

	// ���� �ɼ� ����
	m_socket->SetNoDelay();

	// ���� ����
	// ���� EndPoint �����
	FIPv4Address connectAddr;
	FIPv4Address::Parse(_IP, connectAddr);
	uint16 port = static_cast<uint16>(FCString::Atoi(*_port));
	FIPv4Endpoint endPoint(connectAddr, port);

	if (false == m_socket->Connect(endPoint.ToInternetAddr().Get()))
	{
		// ���� ����
		FString error = m_socketSystem->GetSocketError(m_socketSystem->GetLastErrorCode());
		
		UE_LOG(LogTemp, Error, TEXT("GameInstance - %s"), *error);

		CloseSocket();
		return false;
	}


	// ������ ����� Recv������ �ޱ�
	UE_LOG(LogTemp, Log, TEXT("GameInstance - Connect Server"));

	return true;
}

bool UCGameInstance::SendBytes(const std::vector<uint8>& _bytes)
{
	if (0 == _bytes.size())
	{
		return false;
	}

	int dataSendSize = 0;
	return m_socket->Send(_bytes.data(), _bytes.size(), dataSendSize);
}

bool UCGameInstance::SendFString(const FString& _fstr)
{
	// �𸮾� ���ڵ� �����Լ� ���
	FTCHARToUTF8 convert(*_fstr);
	std::vector<uint8> vecBytes;
	
	vecBytes.resize(convert.Length() + 1);

	memcpy(vecBytes.data(), (ANSICHAR*)convert.Get(), convert.Length());
	vecBytes[convert.Length()] = '\0';

	// ����ȯ
	//FUTF8ToTCHAR rConvert((ANSICHAR*)vecBytes.data());
	//FString recv((TCHAR*)rConvert.Get());

	return SendBytes(vecBytes);
}
