#pragma once

// �뵵 :
// �з� :
// ÷�� :
class ServerHelper
{
public: // member var
	static bool InitSocketLib();

private: // default
	ServerHelper();
	~ServerHelper();

	ServerHelper(const ServerHelper& _other) = delete;
	ServerHelper(ServerHelper&& _other) noexcept;

protected:
	ServerHelper& operator=(const ServerHelper& _other) = delete;
	ServerHelper& operator=(const ServerHelper&& _other) = delete;

private:

public: // member Func
};

