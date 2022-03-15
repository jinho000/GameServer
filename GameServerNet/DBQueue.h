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

// DB���� ������ ó�� ��û�� ���� ť
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

