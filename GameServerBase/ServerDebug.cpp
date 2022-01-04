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

		std::unique_ptr<LogJob> receiveLog(_IOCPworker->GetCompletionKey<LogJob*>());
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

void ServerDebug::Log(LOG_TYPE _type, const std::string& _log)
{
	std::string logText = _log;
	std::unique_ptr<LogJob> sendLog = std::make_unique<LogJob>(_type, logText);
	LogIOCP.PostQueued(0, reinterpret_cast<ULONG_PTR>(sendLog.get()));
	sendLog.release();
}

void ServerDebug::LogError(const std::string& _log)
{
	Log(LOG_TYPE::TYPE_ERROR, _log);
}

void ServerDebug::LogInfo(const std::string& _log)
{
	Log(LOG_TYPE::TYPE_INFO, _log);
}

void ServerDebug::LogWarning(const std::string& _log)
{
	Log(LOG_TYPE::TYPE_WARNING, _log);
}

