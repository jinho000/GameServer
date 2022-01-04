#include "pch.h"
#include "ServerDebug.h"
#include <cassert>

const char* ServerDebug::TypeText[static_cast<int>(LOG_TYPE::SIZE)] = { "ERROR	: ", "WARNING	: ", "INFO	: ", };
ServerIOCP ServerDebug::LogIOCP(&ServerDebug::LogThread, 1);
std::atomic<int> ServerDebug::LogCount = 0;

ServerDebug::ServerDebug()
{
}

void ServerDebug::Initialize()
{
	//LogIOCP.Initialize(&ServerDebug::LogThread, 1);
}

void ServerDebug::Destroy()
{
	LogIOCP.PostQueued(-1, 0);
	Sleep(1);
}


void ServerDebug::LogThread(std::shared_ptr<ServerIOCPWorker> _IOCPworker)
{
	while (true)
	{
		_IOCPworker->Wait(INFINITE);
		if (_IOCPworker->GetNumberOfBytes() == -1)
		{
			break;
		}

		++LogCount;

		std::unique_ptr<LogInfo> receiveLog(_IOCPworker->GetCompletionKey<LogInfo*>());
		std::cout << TypeText[static_cast<int>(receiveLog->logType)] << receiveLog.get()->logText << std::endl;

	}
}

void ServerDebug::AssertDebug()
{
	assert(false);
}

void ServerDebug::AssertDebugMsg(const std::string& _msg)
{
	MessageBoxA(nullptr, _msg.c_str(), "Debug Error", MB_OK);
	AssertDebug();
}

void ServerDebug::Log(LOG_TYPE _type, std::string& _log)
{
	std::unique_ptr<LogInfo> sendLog = std::make_unique<LogInfo>(_type, _log);
	LogIOCP.PostQueued(0, reinterpret_cast<ULONG_PTR>(sendLog.get()));
	sendLog.release();
}
