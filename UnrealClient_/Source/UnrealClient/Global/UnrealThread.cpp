#include "UnrealThread.h"
#include <vector>
#include <Sockets.h>
#include "../Packets/PacketConvertor.h"

UnrealThread::UnrealThread(FSocket* _socket, TQueue<std::shared_ptr<ServerPacketBase>>* _recvQueue)
	: m_recvSocket(_socket)
	, m_pRecvQueue(_recvQueue)
	, m_bAppClose(true)
{
	if (nullptr == m_recvSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("RecvSocket Error"));
	}
}

UnrealThread::~UnrealThread()
{
}

uint32 UnrealThread::Run()
{
	// 리시브 처리 시작
	UE_LOG(LogTemp, Log, TEXT("Recv Start"));

	while (m_bAppClose)
	{
		// Recv 동기 함수로 처리
		std::vector<uint8_t> recvBuffer;
		recvBuffer.resize(1024);
		int readBytes = 0;
		if (false == m_recvSocket->Recv(&recvBuffer[0], recvBuffer.size(), readBytes))
		{
			break;
		}

		UE_LOG(LogTemp, Log, TEXT("Recv data"));

		// 전달받은 패킷을 리시브 큐에 추가
		// 리시브 큐를 각 게임모드에 달린 패킷 컴포넌트 틱에서 처리
		PacketConvertor convertor(recvBuffer);

		check(nullptr != convertor.GetPacket());

		m_pRecvQueue->Enqueue(convertor.GetPacket());
	}

	return 0;
}

void UnrealThread::Stop()
{
	m_bAppClose = false;
}

void UnrealThread::Exit()
{
}
