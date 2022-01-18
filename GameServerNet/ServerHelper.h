#pragma once

// 용도 :
// 분류 :
// 첨언 :
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

