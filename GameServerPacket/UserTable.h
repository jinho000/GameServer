#pragma once
#include <GameServerNet/DBQuery.h>

class UserRow : public std::enable_shared_from_this<UserRow>
{
public:
	int			Index;
	std::string Id;
	std::string Pw;

public:
	UserRow()
		: Index(0)
	{
	}

	UserRow(
		int _Index,
		std::string _Id,
		std::string _Pw
	)
		:Index(_Index),
		Id(_Id),
		Pw(_Pw)
	{
	}
};


// 용도 :
// 분류 :
// 첨언 :
class UserTable
{
// member var
protected:
	static std::string	TableName;

	std::string			Query;		// 실행할 쿼리

public: // default
	UserTable();
	~UserTable();

	UserTable(const UserTable& _other) = delete;
	UserTable(UserTable&& _other) = delete;
	UserTable& operator=(const UserTable& _other) = delete;
	UserTable& operator=(const UserTable&& _other) = delete;

private:

	
public: // member Func
};

class UserTable_SelectIDToUserInfo : public DBQuery, UserTable
{
public:
	std::string ID;
	std::shared_ptr<UserRow> RowData;

public:
	UserTable_SelectIDToUserInfo(std::string _ID);
	bool DoQuery() override;
};


class UserTable_AllUserInfo : public DBQuery, UserTable
{
public:
	std::vector<std::shared_ptr<UserRow>> RowDatas;

public:
	UserTable_AllUserInfo();

	bool DoQuery() override;
};

class UserTable_InsertUserInfo : public DBQuery, UserTable
{
	std::string ID;
	std::string PW;

public:
	UserTable_InsertUserInfo(std::string _ID, std::string _PW);

	bool DoQuery() override;
};