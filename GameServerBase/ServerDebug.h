#pragma once
#include <string>

// �뵵 : ���������ӿ�ũ ����� ���� Ŭ����
// �з� :
// ÷�� :
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

