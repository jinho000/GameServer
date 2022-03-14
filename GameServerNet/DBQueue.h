#pragma once
#include <GameServerBase/ServerQueue.h>
// 용도 :
// 분류 :
// 첨언 :
class DBQueue
{
private: // member var
	

public: // default
	DBQueue();
	~DBQueue();

	DBQueue(const DBQueue& _other) = delete;
	DBQueue(DBQueue&& _other) = delete;

protected:
	DBQueue& operator=(const DBQueue& _other) = delete;
	DBQueue& operator=(const DBQueue&& _other) = delete;

private: // Member Function
	static ServerQueue JobQueue;

public:
	static void Destroy();

public:
	static void Init();
	static void Queue(const std::function<void()>& CallBack);
};

