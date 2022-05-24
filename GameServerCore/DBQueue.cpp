#include "pch.h"
#include "DBQueue.h"
#include <GameServerNet/DBConnecter.h>
#include "ServerCore.h"

ServerQueue DBQueue::WorkQueue;
std::mutex DBQueue::ConnectionRock;

std::vector<DBConnecter*> vecDBConnecter;

void DBQueue::InitDBConnecter(DBConnecter* _DBConnecter)
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

	vecDBConnecter.push_back(_DBConnecter);
}

void DBQueue::Init()
{
	WorkQueue.InitializeLocalData<DBConnecter>(10, "DBThread", InitDBConnecter);
}

void DBQueue::EnQueue(const std::function<void()>& _work)
{
	WorkQueue.Enqueue(_work);
}

void DBQueue::Destroy()
{
	mysql_library_end();

	WorkQueue.Destroy();
}
