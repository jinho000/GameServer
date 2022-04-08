#pragma once
#include <GameServerNet/DBQuery.h>

class ChattingRow : public std::enable_shared_from_this<ChattingRow>
{
public:
	int			index;
	int			userIdx;
	std::string nickName;
	std::string message;

public:
	ChattingRow()
		: userIdx(0)
	{
	}

	ChattingRow(int _index, int _userIndex, std::string _nickName, std::string _message)
		: index(_index)
		, userIdx(_userIndex)
		, nickName(_nickName)
		, message(_message)
	{
	}
};


// 용도 :
// 분류 :
// 첨언 :
class ChattingTable
{
// member var
protected:
	std::string			Query;		// 실행할 쿼리

public: // default
	ChattingTable() = default;
	~ChattingTable() = default;

	ChattingTable(const ChattingTable& _other) = delete;
	ChattingTable(ChattingTable&& _other) = delete;
	ChattingTable& operator=(const ChattingTable& _other) = delete;
	ChattingTable& operator=(const ChattingTable&& _other) = delete;

private:

	
public: // member Func

};

class ChattingTable_InsertChatting : public DBQuery, ChattingTable
{
public:
	int								UserID;
	std::string						NickName;
	std::string						Message;
	std::shared_ptr<ChattingRow>	RowData;

public:
	ChattingTable_InsertChatting(int _userID, const std::string& _nickName, const std::string& _message);
	bool DoQuery() override;
};


