#include "pch.h"
#include "ChattingTable.h"

#include <GameServerNet/DBConnecter.h>
#include <GameServerNet/DBStatement.h>
#include <GameServerNet/DBStatementResult.h>

//////////////////////////////////////////////////////////////////// 

ChattingTable_InsertChatting::ChattingTable_InsertChatting(int _userID, const std::string& _nickName, const std::string& _message)
	: DBQuery("INSERT INTO userver2.chartting (UserIndex, NickName, Message) VALUES (?, ?, ?);")
	, UserID(_userID)
	, NickName(_nickName)
	, Message(_message)
{
}

bool ChattingTable_InsertChatting::DoQuery()
{
	std::unique_ptr<DBStatement> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(UserID);
	Stmt->ParamBindString(NickName);
	Stmt->ParamBindString(Message);
	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////// 