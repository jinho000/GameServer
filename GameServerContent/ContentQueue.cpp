#include "pch.h"
#include "ContentQueue.h"

ServerQueue ContentQueue::WorkQueue;

void ContentQueue::Init()
{
	WorkQueue.Initialize(8, "SessionThread");
}

void ContentQueue::Destroy()
{
	WorkQueue.Destroy();
}

void ContentQueue::EnQueue(const std::function<void()>& _work)
{
	WorkQueue.Enqueue(_work);
}
