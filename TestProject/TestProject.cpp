#include <iostream>
#include <GameServerBase/pch.h>
#include <GameServerNet/pch.h>
#include <GameServerBase/ServerQueue.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/UDPSession.h>
#include <GameServerNet/ServerHelper.h>
#include <GameServerNet/IPEndPoint.h>


void IOCallback(std::shared_ptr<UDPSession> _s, const std::vector<unsigned char>& _b, IPEndPoint& _rEP)
{
	int a = 0;
}

HANDLE IOCPHandle = NULL;
std::thread iocpThread;

void IOCPWorker()
{
	DWORD		 lpNumberOfBytesTransferred;
	ULONG_PTR	 lpCompletionKey;
	LPOVERLAPPED lpOverlapped;
	DWORD		 dwMilliseconds = INFINITE;

	GetQueuedCompletionStatus(IOCPHandle
		, &lpNumberOfBytesTransferred
		, &lpCompletionKey
		, &lpOverlapped
		, dwMilliseconds
	);

	int a = 0;
}

void InitIOCP()
{
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, /*스레드 개수*/ 1);
	iocpThread = std::thread(IOCPWorker);


}

int main()
{
	ServerHelper::InitSocketLib();
	ServerDebug::Initialize();

	ServerQueue netQueue;
	netQueue.Initialize(4);

	IPEndPoint udpEndPoint("127.0.0.1", 30002);
	UDPSession udpSession(udpEndPoint);
	udpSession.BindQueue(netQueue);
	udpSession.SetRecvCallBack(IOCallback);
	udpSession.RequestRecv();


	while (true)
	{
		int value = 1;
		std::cin >> value;
		if (value == 0)
		{
			break;
		}

	}


	ServerDebug::Destroy();

	return 0;
}
