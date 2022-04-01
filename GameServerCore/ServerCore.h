#pragma once
#include <GameServerNet/TCPListener.h>

// ���� ������ �����ִ� Ŭ����
class ServerCore
{
private: // member var
	static TCPListener ServerListener;
	static std::function<void(PtrSTCPSession)> AcceptCallBack;

protected:
	static int			ServerPort;
	static std::string	ServerIP;

	static std::string	DBHost;
	static int			DBPort;
	static std::string	DBName;
	static std::string	DBUser;
	static std::string	DBPW;

protected:
	ServerCore();
	~ServerCore();
	
	ServerCore(const ServerCore& _other) = delete;
	ServerCore(ServerCore&& _other) = delete;
	ServerCore& operator=(const ServerCore& _other) = delete;
	ServerCore& operator=(const ServerCore&& _other) = delete;

protected:
	void SetAcceptCallBack(const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallBack);

private:
	static bool CoreInit();
	static bool CoreRun();
	static bool CoreEnd();

public:
	template<typename UserGameType, typename ... Types>
	static void Start(Types ... args)
	{
		CoreInit();

		// Content���� ������ �۾� ����
		UserGameType NewUserServer = UserGameType(args...);
		NewUserServer.UserStart();

		CoreRun();

		CoreEnd();
	}

private:

public: // member Func

};

