#pragma once
#include <GameServerBase/ServerQueue.h>

// 용도 : DB관련 처리 큐
// 첨언 : 객체로 만들지않고 static으로 사용
class DBConnecter;
class DBQueue
{
private: // member var
	DBQueue();
	~DBQueue();	

public: // default

	DBQueue(const DBQueue& _other) = delete;
	DBQueue(DBQueue&& _other) = delete;

	DBQueue& operator=(const DBQueue& _other) = delete;
	DBQueue& operator=(const DBQueue&& _other) = delete;

private: // mem var
	static ServerQueue JobQueue;
	static std::mutex ConnectionRock;

private:
	static void InitDBConnecter(DBConnecter* _DBConnecter);

public:
	static void Init();
	static void EnQueue(const std::function<void()>& _work);
	static void Destroy();
};

