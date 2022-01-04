#pragma once
#include <string>
#include "ServerIOCP.h"

enum class LOG_TYPE
{
	TYPE_WARNING,
	TYPE_ERROR,
	TYPE_INFO,
	SIZE
};

// �뵵 : ���������ӿ�ũ �����, �α� ���� Ŭ����
// �з� :
// ÷�� : 
class ServerDebug
{
private:
	class LogJob
	{
	public:
		LOG_TYPE logType;
		std::string logText;

		LogJob(LOG_TYPE _logType, std::string& _log)
			: logType(_logType)
			, logText(_log)
		{}
	};

private: // member var
	static const char*		TypeText[static_cast<int>(LOG_TYPE::SIZE)];
	static ServerIOCP		LogIOCP;
	static std::atomic<int> LogCount;

public: // default
	ServerDebug();
	~ServerDebug() = delete;

	ServerDebug(const ServerDebug& _other) = delete;
	ServerDebug(ServerDebug&& _other) = delete;

	static void Initialize();
	static void Destroy();

protected:
	ServerDebug& operator=(const ServerDebug& _other) = delete;
	ServerDebug& operator=(const ServerDebug&& _other) = delete;

private:
	static void LogThread(std::shared_ptr<ServerIOCPWorker> _IOCPworker);

public: // member Func
	static void AssertDebug();
	static void AssertDebugMsg(const std::string& _msg);

	static void Log(LOG_TYPE _type, const std::string& _log);
	static void LogError(const std::string& _log);
	static void LogInfo(const std::string& _log);
	static void LogWarning(const std::string& _log);
};

