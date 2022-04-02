#pragma once
#include <mysql/mysql.h>

// 용도 :
// 분류 :
// 첨언 :
class DBStatement;
class DBConnecter;
class DBStatementResult
{
	friend DBStatement;

private: // member var
	std::vector<unsigned long>	m_resultLengthBuffer;
	std::vector<char>			m_resultIsNullBuffer;
	std::vector<char>			m_resultBindBuffer;

	// 특정할수 없는 정보들을 1개 1개마다 바인드시키는데 사용하는것을 
	// MYSQL_BIND 구조체를 통해서 바인드 시킬수 있다.
	std::vector<MYSQL_BIND>		m_resultBinds;

	DBConnecter*				m_DBConnecterPtr;
	std::string_view			m_query;
	MYSQL_STMT*					m_stmtPtr;

public:
	DBStatementResult(DBConnecter* _DBConneterPtr, MYSQL_STMT* _mysqlStmt, std::string_view _query);

	~DBStatementResult() = default;

	DBStatementResult(const DBStatementResult& _other) = delete;
	DBStatementResult(DBStatementResult&& _other) = delete;
	DBStatementResult& operator=(const DBStatementResult& _other) = delete;
	DBStatementResult& operator=(const DBStatementResult&& _other) = delete;

public:
	bool Next();
	inline uint64_t AffectedRows() { return mysql_stmt_affected_rows(m_stmtPtr); };

	std::string GetString(const int _index);
	int GetInt(const int _index);
	float GetFloat(const int _index);

};

