#pragma once
#include <GameServerBase/ServerQueue.h>

// �뵵 : DB���� ó�� ť
// ÷�� : ��ü�� �������ʰ� static���� ���
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

