#include "pch.h"
#include "Test.h"

#include <iostream>
#include <conio.h>
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerBase/ServerQueue.h>

void Test::TestServerBaseObject()
{

}

void IOCPFunc(std::shared_ptr<ServerIOCPWorker> _iocpWorker)
{
	while (true)
	{
		IocpWaitReturnType returnType = _iocpWorker->Wait(INFINITE);
		std::string logInfo = "test Log";
		ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		

		switch (returnType)
		{
		case IocpWaitReturnType::RETURN_TIMEOUT:
			break;
		case IocpWaitReturnType::RETURN_OK:
			break;
		case IocpWaitReturnType::RETURN_ERROR:
			break;
		default:
			break;
		}

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
