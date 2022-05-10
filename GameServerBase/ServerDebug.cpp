#include "pch.h"
#include "ServerDebug.h"
#include <iostream>
#include <cassert>
#include "ServerQueue.h"

const char* ServerDebug::TypeText[static_cast<int>(LOG_TYPE::SIZE)] = { "ERROR	: ", "WARNING	: ", "INFO	: ", };
ServerQueue* ServerDebug::LogQueue = new ServerQueue;
std::function<void()> ServerDebug::LogWork;
std::atomic<int> ServerDebug::LogCount = 0;

void ServerDebug::Initialize()
{
	LogQueue->Initialize(1, "DebugerThread");
}

void ServerDebug::Destroy()
{
	LogQueue->Destroy();
	delete LogQueue;
}


void ServerDebug::LogThread(LOG_TYPE _type, const std::string& _log)
{
	std::cout << TypeText[static_cast<int>(_type)] << _log << std::endl;
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

void ServerDebug::EnqueueLogWork(LOG_TYPE _type, const std::string& _log)
{
	//LogWork = std::bind(&ServerDebug::LogThread, _type, _log);
	// 
	// 람다캡쳐사용
	LogWork = [_type, _log]() {
		ServerDebug::LogThread(_type, _log);
	};

	LogQueue->Enqueue(LogWork);
}

void ServerDebug::LogError(const std::string& _log)
{
	EnqueueLogWork(LOG_TYPE::TYPE_ERROR, _log);
}

void ServerDebug::LogInfo(const std::string& _log)
{
	EnqueueLogWork(LOG_TYPE::TYPE_INFO, _log);
}

void ServerDebug::LogWarning(const std::string& _log)
{
	EnqueueLogWork(LOG_TYPE::TYPE_WARNING, _log);
}

void ServerDebug::LogErrorAssert(const std::string& _Text)
{
	EnqueueLogWork(LOG_TYPE::TYPE_LASTERROR, _Text);
	AssertDebugMsg(_Text);
}

void ServerDebug::GetLastErrorPrint()
{
	DWORD error = WSAGetLastError();
	char* message = nullptr;

	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&message,
		0,
		nullptr);

	if (nullptr != message)
	{
		// print error message 
		printf_s("Code : %d Message : %s", error, message);
		LocalFree(message);
	}
}
