#include "pch.h"
#include "Test.h"

#include <iostream>
#include <conio.h>
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerBase/ServerQueue.h>
#include <GameServerNet/TCPListener.h>

#include <GameServerNet/enum.h>

void Test::TestServerBaseObject()
{

}

void IOCPFunc(std::shared_ptr<ServerIOCPWorker> _iocpWorker)
{
	while (true)
	{
		_iocpWorker->Wait(INFINITE);
		std::string logInfo = "test Log";
		ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		
		std::cout << "test" << std::endl;
	}
}

void Test::TestIOCP()
{
	ServerIOCP iocp(&IOCPFunc, 3);

	while (true)
	{
		char c = _getch();
		if (c == 'q')
		{
			return;
		}

		iocp.PostQueued(10, 10);
	}
}

void testfunc()
{
	std::cout << "test " << std::endl;
}

void Test::TestServerQueue()
{
	ServerQueue serverQueue(ServerQueue::WORK_TYPE::Default, 1);
	
	serverQueue.Enqueue(testfunc);
}


void Test::TestLog()
{
	ServerIOCP iocp(&IOCPFunc, 10);

	while (true)
	{
		char c = _getch();
		if (c == 'a')
		{
			std::string logInfo = "test Log";
			ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		}
	}

}

void Test::TestListener()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession){
		ServerDebug::LogInfo("접속자가 있습니다");

	});

	_getch();
}
