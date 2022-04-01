#pragma once
#include <GameServerBase/ServerQueue.h>


// DB관련 작업을 처리
class DBConnecter;
class DBQueue1
{
private: // member var
	DBQueue1() = default;
	~DBQueue1() = default;
	DBQueue1(const DBQueue1& _other) = delete;
	DBQueue1(DBQueue1&& _other) = delete;
	DBQueue1& operator=(const DBQueue1& _other) = delete;
	DBQueue1& operator=(const DBQueue1&& _other) = delete;

private: // mem var
	static ServerQueue WorkQueue;
	static std::mutex ConnectionRock;

private:
	static void InitDBConnecter(DBConnecter* _DBConnecter);

public:
	static void Init();
	static void EnQueue(const std::function<void()>& _work);
	static void Destroy();
};

