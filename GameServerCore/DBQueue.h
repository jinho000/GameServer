#pragma once
#include <GameServerBase/ServerQueue.h>


// DB관련 작업을 처리
class DBConnecter;
class DBQueue
{
private: // member var
	DBQueue() = default;
	~DBQueue() = default;
	DBQueue(const DBQueue& _other) = delete;
	DBQueue(DBQueue&& _other) = delete;
	DBQueue& operator=(const DBQueue& _other) = delete;
	DBQueue& operator=(const DBQueue&& _other) = delete;

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

