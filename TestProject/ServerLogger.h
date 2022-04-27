#pragma once
#include <GameServerBase/pch.h>
#include <GameServerBase/ServerQueue.h>
#include <functional>

class ServerLogger
{
private: // member var
	ServerQueue m_logQueue;
	std::function<void()> m_logWork;

public: // default
	ServerLogger();
	~ServerLogger();

	ServerLogger(const ServerLogger& _other) = delete;
	ServerLogger(ServerLogger&& _other) = delete;
	ServerLogger& operator=(const ServerLogger& _other) = delete;
	ServerLogger& operator=(const ServerLogger&& _other) = delete;

private:
	void LogWork(const std::string& _log);

public: // member Func
	void Log(const std::string& _log);
};

