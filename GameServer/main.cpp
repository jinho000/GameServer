#include "pch.h"
#include <iostream>
#include "Test.h"
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <conio.h>

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

int main()
{
	ServerIOCP iocp(&IOCPFunc, 3, INFINITE);

	while (true)
	{
		char c = _getch();
		iocp.PostQueued(10, 10);
	}

	return 0;
}
