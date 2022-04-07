#include "pch.h"
#include "CharacterTable.h"

#include <GameServerNet/DBStatement.h>
#include <GameServerNet/DBStatementResult.h>
#include <GameServerNet/DBConnecter.h>

CharacterTable_SelectNickName::CharacterTable_SelectNickName(std::string _NickName)
	: DBQuery("SELECT Idx, NickName, UserIndex, ATT, HP, LastRoomid, LastRoomPosx, LastRoomPosy, LastRoomPosz FROM userver2.characterinfo WHERE NickName = ? LIMIT 1")
	, NickName(_NickName)
{
}

bool CharacterTable_SelectNickName::DoQuery()
{
	std::unique_ptr<DBStatement> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(NickName);

	std::unique_ptr<DBStatementResult> Result(Stmt->Execute());

	uint64_t Row = Stmt->AffectedRows();

	if (0 >= Row)
	{
		return false;
	}

	Result->Next();

	RowData =
		std::make_shared<CharacterRow>(CharacterRow(
			Result->GetInt(0),
			Result->GetString(1),
			Result->GetInt(2),
			Result->GetFloat(3),
			Result->GetFloat(4),
			Result->GetInt(5),
			Result->GetFloat(6),
			Result->GetFloat(7),
			Result->GetFloat(8)
		));


	return true;
}

/// ///////////////////////// CharacterTable_SelectUserCharacters

CharacterTable_SelectUserCharacters::CharacterTable_SelectUserCharacters(int _userIdx)
	: DBQuery("SELECT Idx, NickName, UserIndex, ATT, HP, LastRoomid, LastRoomPosx, LastRoomPosy, LastRoomPosz FROM userver2.characterinfo WHERE UserIndex = ?")
	, UserIndex(_userIdx)
{
}

bool CharacterTable_SelectUserCharacters::DoQuery()
{
	std::unique_ptr<DBStatement> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(UserIndex);

	std::unique_ptr<DBStatementResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);


	while (Result->Next())
	{
		RowDatas.push_back(
			std::make_shared<CharacterRow>(CharacterRow(
				Result->GetInt(0),
				Result->GetString(1),
				Result->GetInt(2),
				Result->GetFloat(3),
				Result->GetFloat(4),
				Result->GetInt(5),
				Result->GetFloat(6),
				Result->GetFloat(7),
				Result->GetFloat(8)
			))
		);
	}

	return true;
}



/// ///////////////////////// CharacterTable_SelectUserCharacters

CharacterTable_CreateCharacter::CharacterTable_CreateCharacter(std::string _NickName, int _userId)
	: DBQuery("INSERT INTO userver2.characterinfo (NickName, UserIndex) VALUES (?, ?);")
	, NickName(_NickName)
	, UserId(_userId)
{
}

bool CharacterTable_CreateCharacter::DoQuery()
{
	std::unique_ptr<DBStatement> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(NickName);
	Stmt->ParamBindInt(UserId);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

CharacterTable_DeleteCharacter::CharacterTable_DeleteCharacter(int _characterIndex)
	: DBQuery("DELETE FROM userver2.characterinfo WHERE Idx = ?;")
	, _characterIndex(_characterIndex)
{
}

bool CharacterTable_DeleteCharacter::DoQuery()
{
	std::unique_ptr<DBStatement> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(_characterIndex);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}
