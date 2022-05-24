#pragma once
#include "DBStatement.h"

// 용도 : DB에 연결하기 위한 클래스
// 분류 :
// 첨언 
// 한번 연결하면 끊어지지 않음
//
struct MYSQL;
class DBConnecter
{
private: // member var
	MYSQL* m_mysqlPtr;

public: // default
	DBConnecter();
	~DBConnecter();

	DBConnecter(const DBConnecter& _other) = delete;
	DBConnecter(DBConnecter&& _other) = delete;
	DBConnecter& operator=(const DBConnecter& _other) = delete;
	DBConnecter& operator=(const DBConnecter&& _other) = delete;

private:

public: // member Func
	bool Connect(
		const std::string _Host,
		const std::string _Id,
		const std::string _Pw,
		const std::string _Schema,
		unsigned int _Port
	);

	std::unique_ptr<DBStatement> CreateStmt(std::string_view _Query);
	std::string GetLastError();

};

