#include "pch.h"
#include "DBStatementResult.h"

DBStatementResult::DBStatementResult(DBConnecter* _DBConneterPtr, MYSQL_STMT* _mysqlStmt, std::string_view _query)
	: m_DBConnecterPtr(_DBConneterPtr)
	, m_query(_query)
	, m_stmtPtr(_mysqlStmt)
{
	m_resultLengthBuffer.reserve(20);
	m_resultIsNullBuffer.reserve(20);
	m_resultBindBuffer.reserve(1024);
}

bool DBStatementResult::Next()
{
	// 다음게 없다면 0 != 다음녀석이 없다.
	return 0 == mysql_stmt_fetch(m_stmtPtr);
}

std::string DBStatementResult::GetString(const int _index)
{
	return std::string(reinterpret_cast<char*>(m_resultBinds[_index].buffer));
}

int DBStatementResult::GetInt(const int _index)
{
	return *reinterpret_cast<int32_t*>(m_resultBinds[_index].buffer);
}

float DBStatementResult::GetFloat(const int _index)
{
	return *reinterpret_cast<float*>(m_resultBinds[_index].buffer);
}
