#pragma once
#include <GameServerBase/ServerQueue.h>

// 네트워크상에서 통신하는 일을 처리
class NetQueue
{
private: // Member Function
	static ServerQueue WorkQueue;

private: // default
	NetQueue() = default;
	~NetQueue() = default;

	NetQueue(const NetQueue& _other) = delete;
	NetQueue(NetQueue&& _other) = delete;
	NetQueue& operator=(const NetQueue& _other) = delete;
	NetQueue& operator=(const NetQueue&& _other) = delete;


public: // member Func
	static void Init();
	static void Destroy();
	static void EnQueue(const std::function<void()>& _work);

	static const ServerQueue& GetQueue() { return WorkQueue; }
};

