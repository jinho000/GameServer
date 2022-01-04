#pragma once
#include <string>
#include "ServerIOCP.h"

enum class LOG_TYPE
{
	TYPE_WARRNING,
	TYPE_ERROR,
	TYPE_INFO,
	SIZE
};

// 용도 : 서버프레임워크 디버그, 로그 관련 클래스
// 분류 :
// 첨언 : 
class ServerDebug
{
private:
	class LogInfo
	{
	public:
		LOG_TYPE logType;
		std::string logText;

		LogInfo(LOG_TYPE _logType, std::string& _log)
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
	static void Log(LOG_TYPE _type, std::string& _log);
};

