#pragma once
#include <GameServerBase/ServerQueue.h>

class TestClass
{
public:
	int Value;

public:
	TestClass()
	{
		int a = 0;
	}

	virtual ~TestClass()
	{
		int a = 0;
	}
};

// DB관련 데이터 처리 요청을 위한 큐
class DBQueue
{
private: // member var
	static ServerQueue JobQueue;
	

public: // default
	DBQueue();
	~DBQueue();

	DBQueue(const DBQueue& _other) = delete;
	DBQueue(DBQueue&& _other) = delete;

protected:
	DBQueue& operator=(const DBQueue& _other) = delete;
	DBQueue& operator=(const DBQueue&& _other) = delete;

private:

public:
	static void Init();
	static void EnQueue(const std::function<void()>& _callback);

};

