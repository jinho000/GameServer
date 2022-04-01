#include "pch.h"
#include "NetQueue.h"

ServerQueue NetQueue::WorkQueue;

void NetQueue::Init()
{
	WorkQueue.Initialize(ServerQueue::WORK_TYPE::Default, 8, "NetQueue");
}

void NetQueue::Destroy()
{
	WorkQueue.Destroy();
}

void NetQueue::EnQueue(const std::function<void()>& _work)
{
	WorkQueue.Enqueue(_work);
}
