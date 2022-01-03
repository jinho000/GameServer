#pragma once
#include <string>

// 용도 : 서버프레임워크 디버그 관련 클래스
// 분류 :
// 첨언 :
class ServerDebug
{
private: // member var
	

public: // default
	ServerDebug();
	~ServerDebug();

	ServerDebug(const ServerDebug& _other) = delete;
	ServerDebug(ServerDebug&& _other) noexcept;

protected:
	ServerDebug& operator=(const ServerDebug& _other) = delete;
	ServerDebug& operator=(const ServerDebug&& _other) = delete;

private:

public: // member Func
	static void AssertDebug();
	static void AssertDebugMsg(const std::string& _msg);
};

