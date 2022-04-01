#include "pch.h"
#include "DBQueue.h"

#include <GameServerNet/DBConnecter.h>

ServerQueue DBQueue::JobQueue;
std::mutex DBQueue::ConnectionRock;

DBQueue::DBQueue()
{
}

DBQueue::~DBQueue()
{
}

void DBQueue::InitDBConnecter(DBConnecter* _DBConnecter)
{
	std::lock_guard<std::mutex> lockGuard(ConnectionRock);

	if (nullptr == _DBConnecter)
	{
		ServerDebug::AssertDebugMsg("DbConnecter Is Nullptr");
		return;
	}

	if (false == _DBConnecter->Connect("127.0.0.1", "root", "1234", "gameserver", 3306))
	{
		std::string Error = _DBConnecter->GetLastError();
		ServerDebug::AssertDebugMsg("DbConnecter Is Connection Error" + Error);
		return;
	}

	ServerDebug::LogInfo("DBConnect");

}

void DBQueue::Init()
{
	JobQueue.InitializeLocalData<DBConnecter>(ServerQueue::WORK_TYPE::Default, 20, "DBThread", InitDBConnecter);
}

void DBQueue::EnQueue(const std::function<void()>& _work)
{
	JobQueue.Enqueue(_work);
}

void DBQueue::Destroy()
{

}
