#include "pch.h"
#include "Test.h"

#include <conio.h>
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <GameServerBase/ServerDebug.h>

void Test::TestServerBaseObject()
{

}

void IOCPFunc(std::shared_ptr<ServerIOCPWorker> _iocpWorker)
{
	while (true)
	{
		IocpWaitReturnType returnType = _iocpWorker->Wait(1000);
		
		std::string logInfo = "test Log";
		ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		

		//switch (returnType)
		//{
		//case IocpWaitReturnType::RETURN_TIMEOUT:
		//	break;
		//case IocpWaitReturnType::RETURN_POST:
		//	break;
		//case IocpWaitReturnType::RETURN_ERROR:
		//	break;
		//default:
		//	break;
		//}

		//std::cout << "test" << std::endl;
	}
}

void Test::TestIOCP()
{
	ServerIOCP iocp(&IOCPFunc, 3);

	while (true)
	{
		char c = _getch();
		iocp.PostQueued(10, 10);
	}
}


void Test::TestLog()
{
	ServerDebug::Initialize();

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

	ServerDebug::Destroy();
}
