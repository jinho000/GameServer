#include "pch.h"
#include "DBQuery.h"
#include <GameServerBase/ServerThread.h>
#include "DBConnecter.h"

DBQuery::DBQuery(const char* _Query)
	: DBConnecterPtr(ServerThread::GetLocalData<DBConnecter>())
	, QueryString(_Query)
{
}

DBQuery::~DBQuery()
{
}
