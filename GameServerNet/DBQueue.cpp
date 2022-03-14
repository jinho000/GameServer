#include "pch.h"
#include "DBQueue.h"

DBQueue::DBQueue()
{
}

DBQueue::~DBQueue()
{
}

void DBQueue::Init() {
	JobQueue.Initialize(GameServerQueue::WORK_TYPE::Default, 20, "DBThread");
}

void DBQueue::Queue(const std::function<void()>& CallBack)
{
	JobQueue.EnQueue(CallBack);
}

void DBQueue::Destroy()
{
	JobQueue.Destroy();
}