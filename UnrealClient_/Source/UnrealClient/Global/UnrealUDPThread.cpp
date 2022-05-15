#include "UnrealUDPThread.h"
#include <Sockets.h>
#include "../Packets/PacketConvertor.h"

UnrealUDPThread::UnrealUDPThread(ISocketSubsystem* _socketSubSystem, FSocket* _socket, TQueue<std::shared_ptr<ServerPacketBase>>* _recvQueue)
	: m_socketSubSystem(_socketSubSystem)
	, m_recvSocket(_socket)
	, m_pRecvQueue(_recvQueue)
	, m_bAppClose(true)
{
}

UnrealUDPThread::~UnrealUDPThread()
{
}

uint32 UnrealUDPThread::Run()
{
	// ���ú� ó�� ����
	UE_LOG(LogTemp, Log, TEXT("UDP Recv Start"));

	while (m_bAppClose)
	{
		// Recv ���� �Լ��� ó��
		std::vector<uint8_t> recvBuffer;
		recvBuffer.resize(1024);
		int readBytes = 0;

		if (false == m_recvSocket->Recv(&recvBuffer[0], recvBuffer.size(), readBytes))
		{
			auto Result = m_recvSocket->GetConnectionState();

			switch (Result)
			{
			case SCS_NotConnected:
				break;
			case SCS_Connected:
			{
				// ������ ����Ǿ�����
				// ������ �и�������
				// ���� ������ Ŀ��Ʈ ���¶�� ó���ȴ�.
				// ThreadHandlerServerDestroy
				//ServerDestroyMessage SDM;
				//GameServerSerializer Sr;
				//SDM.Serialize(Sr);
				//MessageConverter Converter = MessageConverter(Sr.GetData());
				//MessageQueue_->Enqueue(Converter.GetServerMessage());
				return 0;
			}
			case SCS_ConnectionError:
				// ���� ���� ����������
				// �ƹ��͵� ���ʿ䰡 ����.
				break;
			default:
				break;
			}

			// while�� ����
			m_bAppClose = false;
			break;
		}


		// ���޹��� ��Ŷ�� ���ú� ť�� �߰�
		// ���ú� ť�� �� ���Ӹ�忡 �޸� ��Ŷ ������Ʈ ƽ���� ó��
		PacketConvertor convertor(recvBuffer);
		check(nullptr != convertor.GetPacket());

		m_pRecvQueue->Enqueue(convertor.GetPacket());
	}


	return 0;
}

void UnrealUDPThread::Close()
{
	m_bAppClose = false;
}
