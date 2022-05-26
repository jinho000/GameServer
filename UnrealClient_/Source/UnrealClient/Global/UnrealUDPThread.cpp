#include "UnrealUDPThread.h"
#include <Sockets.h>
#include <vector>
#include <SocketSubSystem.h>
#include <Networking.h>
#include "../Packets/PacketConvertor.h"

UnrealUDPThread::UnrealUDPThread(ISocketSubsystem* _socketSubSystem, FSocket* _socket, TQueue<std::shared_ptr<ServerPacketBase>>* _recvQueue)
	: m_socketSubSystem(_socketSubSystem)
	, m_bAppClose(true)
	, m_bRun(true)
	, m_recvSocket(_socket)
	, m_pRecvQueue(_recvQueue)
{
}

UnrealUDPThread::~UnrealUDPThread()
{
}

uint32 UnrealUDPThread::Run()
{
	// 리시브 처리 시작
	UE_LOG(LogTemp, Log, TEXT("UDP Recv Start"));
	
	while (m_bAppClose)
	{
		if (false == m_bRun)
		{
			continue;
		}

		FIPv4Endpoint ConnectAddress_ = FIPv4Endpoint();
		TSharedRef<FInternetAddr> Ref = ConnectAddress_.ToInternetAddr();
		std::vector<uint8_t> recvBuffer;
		recvBuffer.resize(1024);
		int readBytes = 0;

		// Recv 동기 함수로 처리
		if (false == m_recvSocket->RecvFrom(&recvBuffer[0], recvBuffer.size(), readBytes, Ref.Get(), ESocketReceiveFlags::Type::None))
		{
			ESocketErrors Error2 = m_socketSubSystem->GetLastErrorCode();
			FString Debug = m_recvSocket->GetDescription();

			UE_LOG(LogTemp, Error, TEXT("%d"), Error2);

			break;
		}


		// 전달받은 패킷을 리시브 큐에 추가
		// 리시브 큐를 각 게임모드에 달린 패킷 컴포넌트 틱에서 처리
		PacketConvertor convertor(recvBuffer);
		check(nullptr != convertor.GetPacket());

		m_pRecvQueue->Enqueue(convertor.GetPacket());
	}


	return 0;
}

void UnrealUDPThread::Destroy()
{
	m_bAppClose = false;
}

void UnrealUDPThread::RunThread()
{
	m_bRun = true;
}

void UnrealUDPThread::StopThread()
{
	m_bRun = false;
}
