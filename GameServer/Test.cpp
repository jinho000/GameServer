#include "pch.h"
#include "Test.h"

#include <conio.h>
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>

void Test::TestServerBaseObject()
{

}

void IOCPFunc(std::shared_ptr<ServerIOCPWorker> _iocpWorker)
{
	while (true)
	{
		IocpWaitReturnType returnType = _iocpWorker->Wait();

		switch (returnType)
		{
		case IocpWaitReturnType::RETURN_TIMEOUT:
			break;
		case IocpWaitReturnType::RETURN_POST:
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
	ServerIOCP iocp(&IOCPFunc, 3, INFINITE);

	while (true)
	{
		char c = _getch();
		iocp.PostQueued(10, 10);
	}
}
