#include "pch.h"
#include "DBQueue.h"

ServerQueue DBQueue::JobQueue;

DBQueue::DBQueue()
{
}

DBQueue::~DBQueue()
{
}

void DBQueue::Init()
{
	JobQueue.InitializeLocalData<TestClass>(ServerQueue::WORK_TYPE::Default, 20, "DBThread");
}

void DBQueue::EnQueue(const std::function<void()>& _callback)
{
	JobQueue.Enqueue(_callback);
}

