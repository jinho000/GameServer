// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"
#include <Sockets.h>
#include <SocketSubsystem.h>
#include <Interfaces/IPv4/IPv4Address.h>
#include <Interfaces/IPv4/IPv4Endpoint.h>

#include "CBlueprintFunctionLibrary.h"

UCGameInstance::UCGameInstance()
	: m_recvThread(nullptr)
	, m_runnableThread(nullptr)
	, m_UDPRecvThread(nullptr)
	, m_UDPrunnableThread(nullptr)
	, m_socketSystem(nullptr)
	, m_socket(nullptr)
	, m_UDPsocket(nullptr)
	, m_serverIP("127.0.0.1")
	, m_TCPServerPort(-1)
	, m_UDPServerPort(-1)
	, m_unrealUDPPort(35000)
	, LoginProcess(false)
	, m_sessionIdx(-1)
	, m_playerIdx(-1)

{
	int a = 0;
}

UCGameInstance::~UCGameInstance()
{
}

void UCGameInstance::CloseSocket()
{
	// 소켓 종료
	if (nullptr != m_socket)
	{
		m_socket->Close();
		m_socket = nullptr;
	}

	if (nullptr != m_UDPsocket)
	{
		m_UDPsocket->Close();
		m_UDPsocket = nullptr;
	}
}

bool UCGameInstance::ConnectServer(const FString& _IP, const FString& _port)
{
	// 이미 서버에 연결된 경우
	if (nullptr != m_socket)
	{
		return true;
	}

	m_serverIP = _IP;
	m_TCPServerPort = static_cast<uint16>(FCString::Atoi(*_port));

	

	// 소켓 만들기
	m_socketSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	FString socketDesc = TEXT("Socket Description");
	m_socket = m_socketSystem->CreateSocket(NAME_Stream, socketDesc, false);
	if (nullptr == m_socket)
	{
		// 소켓 생성 실패
		UE_LOG(LogTemp, Error, TEXT("GameInstance - Create Socket Error"));
		return false;
	}

	// 소켓 옵션 설정
	m_socket->SetNoDelay();

	// 소켓 연결
	// 소켓 EndPoint 만들기
	FIPv4Address connectAddr;
	FIPv4Address::Parse(m_serverIP, connectAddr);
	FIPv4Endpoint endPoint(connectAddr, m_TCPServerPort);

	if (false == m_socket->Connect(endPoint.ToInternetAddr().Get()))
	{
		// 접속 실패
		FString error = m_socketSystem->GetSocketError(m_socketSystem->GetLastErrorCode());
		UE_LOG(LogTemp, Error, TEXT("GameInstance - %s"), *error);

		CloseSocket();
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("GameInstance - Connect Server"));

	// 스레드 만들어 Recv데이터 받기
	m_recvThread = new UnrealThread(m_socket, &m_packetQueue);
	m_runnableThread = FRunnableThread::Create(m_recvThread, TEXT("Recv Thread"));
	
	return true;
}

bool UCGameInstance::ConnectUDPServer()
{
	if (nullptr == m_socketSystem)
	{
		return false;
	}

	// 소켓 생성
	m_UDPsocket = m_socketSystem->CreateSocket(NAME_DGram, TEXT("Unreal UDP Socket"));
	if (nullptr == m_UDPsocket)
	{
		UE_LOG(LogTemp, Error, TEXT("UDP Socket Create Error"));
		return false;
	}

	// 소켓 생성을 위해 endpoint생성
	FIPv4Address connectAddress;
	FIPv4Address::Parse(m_serverIP, connectAddress);
	FIPv4Endpoint unrealUDPEndPoint = FIPv4Endpoint(connectAddress, m_unrealUDPPort);

	// 소켓을 udp endpoint에 연결
	while (false == m_UDPsocket->Bind(unrealUDPEndPoint.ToInternetAddr().Get()))
	{
		// 실패시 포트 번호를 바꿔 다시 시도
		UE_LOG(LogTemp, Error, TEXT("socket bind fail"));
		UE_LOG(LogTemp, Error, TEXT("change unrealUDPPort"));
		unrealUDPEndPoint = FIPv4Endpoint(connectAddress, ++m_unrealUDPPort);
	}

	return true;
}

void UCGameInstance::StartUDPThread()
{
	if (nullptr == m_UDPRecvThread)
	{
		// recv Thread 생성
		m_UDPRecvThread = new UnrealUDPThread(m_socketSystem, m_UDPsocket, &m_packetQueue);
		m_UDPrunnableThread = FRunnableThread::Create(m_UDPRecvThread, TEXT("UDP Recv Thread"));
	}
	
	m_UDPRecvThread->RunThread();
}

void UCGameInstance::EndUPDThread()
{
	m_UDPRecvThread->StopThread();
}

bool UCGameInstance::SendBytes(const std::vector<uint8>& _bytes)
{
	if (0 == _bytes.size())
	{
		UE_LOG(LogTemp, Log, TEXT("GameInstance - Byte Size is 0"));
		return false;
	}

	if (nullptr == m_socket)
	{
		UE_LOG(LogTemp, Log, TEXT("GameInstance - Not Connected"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Send Packet"));

	int dataSendSize = 0;
	return m_socket->Send(_bytes.data(), _bytes.size(), dataSendSize);
}

bool UCGameInstance::SendUDP(const std::vector<uint8>& _packet)
{
	if (nullptr == m_UDPsocket)
	{
		return false;
	}

	if (0 == _packet.size())
	{
		return false;
	}

	int32 DataSendSize = 0;

	return m_UDPsocket->SendTo(&_packet[0], _packet.size(), DataSendSize, m_serverUDPEndPoint.ToInternetAddr().Get());
}

void UCGameInstance::AddServerPacket(std::shared_ptr<ServerPacketBase> _serverPacket)
{
	m_packetQueue.Enqueue(_serverPacket);
}

void UCGameInstance::SetUDPEndPoint(int serverUDPPort)
{
	m_UDPServerPort = serverUDPPort;

	// udp server endpoint 만들기
	// send 보내기위해 저장
	FIPv4Address connectAddress;
	FIPv4Address::Parse(m_serverIP, connectAddress);
	m_serverUDPEndPoint = FIPv4Endpoint(connectAddress, m_UDPServerPort);
}

void UCGameInstance::DeleteCharacter(const std::string& _deleteNickName)
{
	auto iter = UserCharacterList.begin();

	while (iter != UserCharacterList.end())
	{
		if (iter->NickName == _deleteNickName)
		{
			UserCharacterList.erase(iter);
			return;
		}

		++iter;
	}
}

void UCGameInstance::SetPlayerID(uint64_t playerID)
{
	m_playerID = playerID;
}

void UCGameInstance::SetSessionIdx(int sessionIdx)
{
	m_sessionIdx = sessionIdx;
}

void UCGameInstance::SetPlayerIdx(int playerIdx)
{
	m_playerIdx = playerIdx;
}

void UCGameInstance::SetOtherPlayerID(const std::vector<uint64_t>& otherPlayerID)
{
	m_otherPlayerID = otherPlayerID;
}

uint64_t UCGameInstance::GetPlayerID()
{
	return m_playerID;
}

int UCGameInstance::GetSessionIdx()
{
	return m_sessionIdx;
}

int UCGameInstance::GetPlayerIdx()
{
	return m_playerIdx;
}

const std::vector<uint64_t>& UCGameInstance::GetOtherPlayerID()
{
	return m_otherPlayerID;
}


//bool UCGameInstance::SendFString(const FString& _fstr)
//{
//	// 언리얼 인코딩 헬퍼함수 사용
//	FTCHARToUTF8 convert(*_fstr);
//	std::vector<uint8> vecBytes;
//	
//	vecBytes.resize(convert.Length() + 1);
//
//	memcpy(vecBytes.data(), (ANSICHAR*)convert.Get(), convert.Length());
//	vecBytes[convert.Length()] = '\0';
//
//	// 역변환
//	//FUTF8ToTCHAR rConvert((ANSICHAR*)vecBytes.data());
//	//FString recv((TCHAR*)rConvert.Get());
//
//	return SendBytes(vecBytes);
//}
