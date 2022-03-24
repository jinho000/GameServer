#pragma once
#include <mysql/mysql.h>
#include "DBStatementResult.h"

// 용도 :
// 분류 :
// 첨언 :
class DBConnecter;
class DBStatement : public std::enable_shared_from_this<DBStatement>
{
private: // member var
	// 바인드 시키기 위한 정보체를 만들어줘야 합니다.
	std::vector<unsigned long>	m_paramLengthBuffer;
	std::vector<char>			m_paramIsNullBuffer;
	std::vector<char>			m_paramBindBuffer;
	std::vector<MYSQL_BIND>		m_parambinds;

	DBConnecter*				m_DBConnecterPtr;
	std::string_view			m_query;
	MYSQL_STMT*					m_stmtPtr;

public: // default
	DBStatement(DBConnecter* _Ptr, MYSQL_STMT* _stmt, std::string_view _Query);
	DBStatement() = delete;
	~DBStatement() = default;

	DBStatement(const DBStatement& _other) = delete;
	DBStatement(DBStatement&& _other) = delete;
	DBStatement& operator=(const DBStatement& _other) = delete;
	DBStatement& operator=(const DBStatement&& _other) = delete;

public: // member Func
	void ParamBindString(std::string_view _Value);
	void ParamBindInt(const int _Value);
	void ParamBindFloat(const float _Value);

public:
	std::unique_ptr<DBStatementResult> Execute();

	// uint64_t Id = mysql_stmt_insert_id(Stmt_);
	// 오토인클리먼트 했을때 아이디가 나올겁니다.
	inline uint64_t InsertId() { return mysql_stmt_insert_id(m_stmtPtr); };
	inline uint64_t AffectedRows() { return mysql_stmt_affected_rows(m_stmtPtr); };
};
