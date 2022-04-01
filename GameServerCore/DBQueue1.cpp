#include "pch.h"
#include "DBQueue1.h"
#include <GameServerNet/DBConnecter.h>
#include "ServerCore.h"

ServerQueue DBQueue1::WorkQueue;
std::mutex DBQueue1::ConnectionRock;

void DBQueue1::InitDBConnecter(DBConnecter* _DBConnecter)
{
	std::lock_guard<std::mutex> lockGuard(ConnectionRock);

	if (nullptr == _DBConnecter)
	{
		ServerDebug::AssertDebugMsg("DbConnecter Is Nullptr");
		return;
	}

	const DBInfo dbConfig = ServerCore::GetDBInfo();

	if (false == _DBConnecter->Connect(
		dbConfig.DBHost,
		dbConfig.DBUser,
		dbConfig.DBPW,
		dbConfig.DBName,
		dbConfig.DBPort))
	{
		std::string Error = _DBConnecter->GetLastError();
		ServerDebug::AssertDebugMsg("DbConnecter Is Connection Error" + Error);
		return;
	}

	ServerDebug::LogInfo("DBConnect");

}

void DBQueue1::Init()
{
	WorkQueue.InitializeLocalData<DBConnecter>(ServerQueue::WORK_TYPE::Default, 10, "DBThread", InitDBConnecter);
}

void DBQueue1::EnQueue(const std::function<void()>& _work)
{
	WorkQueue.Enqueue(_work);
}

void DBQueue1::Destroy()
{
	WorkQueue.Destroy();
}
