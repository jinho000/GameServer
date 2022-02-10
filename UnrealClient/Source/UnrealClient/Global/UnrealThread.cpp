#include "UnrealThread.h"
#include <vector>
#include <Sockets.h>
#include "../Packets/PacketConvertor.h"

UnrealThread::UnrealThread(FSocket* _socket, TQueue<std::shared_ptr<ClientPacketBase>>* _recvQueue)
	: m_recvSocket(_socket)
	, m_recvQueue(_recvQueue)
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
	// ���ú� ó�� ����
	UE_LOG(LogTemp, Log, TEXT("Recv Start"));

	while (true)
	{
		// Recv ���� �Լ��� ó��
		std::vector<uint8_t> recvBuffer;
		recvBuffer.resize(1024);
		int readBytes = 0;
		if (false == m_recvSocket->Recv(&recvBuffer[0], recvBuffer.size(), readBytes))
		{
			break;
		}

		// ���޹��� ��Ŷ�� ���ú� ť�� �߰�
		PacketConvertor convertor(recvBuffer);
		m_recvQueue->Enqueue(convertor.GetPacket());
	}

	return 0;
}

void UnrealThread::Stop()
{
}

void UnrealThread::Exit()
{
}
