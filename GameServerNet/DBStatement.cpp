#include "pch.h"
#include "DBStatement.h"

#include <GameServerBase/ServerDebug.h>

#include "DBConnecter.h"

DBStatement::DBStatement(DBConnecter* _DBConnecterPtr, MYSQL_STMT* _stmt, std::string_view _Query)
	: m_DBConnecterPtr(_DBConnecterPtr)
	, m_query(_Query)
	, m_stmtPtr(_stmt)
{
	m_paramLengthBuffer.reserve(20);
	m_paramIsNullBuffer.reserve(20);
	m_paramBindBuffer.reserve(1024);
}

void DBStatement::ParamBindString(std::string_view _Value)
{
	m_paramLengthBuffer.emplace_back();
	m_paramIsNullBuffer.emplace_back();
	size_t Size = m_paramBindBuffer.size();
	m_paramBindBuffer.resize(m_paramBindBuffer.size() + _Value.size());

	// 선확장 후보고
	MYSQL_BIND& Bind = m_parambinds.emplace_back();
	Bind.buffer_type = MYSQL_TYPE_VARCHAR;
	Bind.buffer = &m_paramBindBuffer[Size];
	memset(Bind.buffer, 0x00, _Value.size() + 1);
	memcpy_s(Bind.buffer, _Value.length(), _Value.data(), _Value.length());
	Bind.buffer_length = static_cast<unsigned long>(_Value.length());
	Bind.is_null = reinterpret_cast<bool*>(&m_paramIsNullBuffer[m_paramIsNullBuffer.size() - 1]);
	*Bind.is_null = false;
	Bind.length = &m_paramLengthBuffer[m_paramLengthBuffer.size() - 1];
	*Bind.length = Bind.buffer_length;
}

void DBStatement::ParamBindInt(const int _Value)
{
	m_paramLengthBuffer.emplace_back();
	m_paramIsNullBuffer.emplace_back();
	size_t Size = m_paramBindBuffer.size();
	m_paramBindBuffer.resize(m_paramBindBuffer.size() + sizeof(int));

	// 선확장 후보고
	MYSQL_BIND& Bind = m_parambinds.emplace_back();
	Bind.buffer_type = MYSQL_TYPE_LONG;
	Bind.buffer = &m_paramBindBuffer[Size];
	memset(Bind.buffer, 0x00, sizeof(int));
	memcpy_s(Bind.buffer, sizeof(int), &_Value, sizeof(int));
	Bind.buffer_length = static_cast<unsigned long>(sizeof(int));
	Bind.is_null = reinterpret_cast<bool*>(&m_paramIsNullBuffer[m_paramIsNullBuffer.size() - 1]);
	*Bind.is_null = false;
	Bind.length = &m_paramLengthBuffer[m_paramLengthBuffer.size() - 1];
	*Bind.length = Bind.buffer_length;
}

void DBStatement::ParamBindFloat(const float _Value)
{
}

std::unique_ptr<DBStatementResult> DBStatement::Execute()
{
	// ?가 1개인데
	int ParamCount = mysql_stmt_param_count(m_stmtPtr);

	// 바인드는 아직 안되어있고
	// 넣어놓지 않았으면 안된다.
	if (ParamCount != m_parambinds.size())
	{
		ServerDebug::AssertDebugMsg("query bind count not Equal");
		return nullptr;
	}

	if (0 != ParamCount)
	{
		if (0 != mysql_stmt_bind_param(m_stmtPtr, &m_parambinds[0]))
		{
			ServerDebug::AssertDebugMsg("mysql_stmt_bind_param Error" + m_DBConnecterPtr->GetLastError());
			return nullptr;
		}
	}

	MYSQL_RES* ResultMetaData = mysql_stmt_result_metadata(m_stmtPtr);
	// 당연히 이 쿼리가 select 쿼리가 아니라면
	// 결과값이 없을수가 있죠?

	std::unique_ptr<DBStatementResult> Result = nullptr;

	if (nullptr != ResultMetaData)
	{
		Result = std::make_unique<DBStatementResult>(m_DBConnecterPtr, m_stmtPtr, m_query);

		// 이게 nullptr이 아니라면 결과값이 나올거라는 이야기이가 되고
		// 결과값의 columncount와 그 row카운트를 알아내야 한다.
		int ColumnCount = mysql_num_fields(ResultMetaData);
		for (size_t i = 0; i < ColumnCount; i++)
		{
			MYSQL_BIND& ResultBind = Result->m_resultBinds.emplace_back();
			Result->m_resultIsNullBuffer.emplace_back();
			Result->m_resultLengthBuffer.emplace_back();

			MYSQL_FIELD& field = ResultMetaData->fields[i];

			size_t BufferStart = Result->m_resultBindBuffer.size();
			// 나는 int에요
			// 나는 string이에요
			switch (field.type)
			{
			case enum_field_types::MYSQL_TYPE_VAR_STRING:
			{
				Result->m_resultBindBuffer.resize(Result->m_resultBindBuffer.size() + field.length + 1);
				ResultBind.buffer_type = enum_field_types::MYSQL_TYPE_VAR_STRING;
				ResultBind.buffer = &Result->m_resultBindBuffer[BufferStart];
				// ResultBind.buffer = new char[field.length + 1];
				ResultBind.buffer_length = field.length + 1;
				memset(ResultBind.buffer, 0x00, field.length + 1);
				ResultBind.is_null = reinterpret_cast<bool*>(&Result->m_resultIsNullBuffer[Result->m_resultIsNullBuffer.size() - 1]);
				*ResultBind.is_null = false;
				ResultBind.length = &Result->m_resultLengthBuffer[Result->m_resultLengthBuffer.size() - 1];
				break;
			}
			case enum_field_types::MYSQL_TYPE_LONG:
			{
				Result->m_resultBindBuffer.resize(Result->m_resultBindBuffer.size() + sizeof(int));
				ResultBind.buffer_type = enum_field_types::MYSQL_TYPE_LONG;
				ResultBind.buffer = &Result->m_resultBindBuffer[BufferStart];
				// ResultBind.buffer = new char[sizeof(int)];
				ResultBind.buffer_length = sizeof(int);
				memset(ResultBind.buffer, 0x00, sizeof(int));
				ResultBind.is_null = reinterpret_cast<bool*>(&Result->m_resultIsNullBuffer[Result->m_resultIsNullBuffer.size() - 1]);
				*ResultBind.is_null = false;
				ResultBind.length = &Result->m_resultLengthBuffer[Result->m_resultLengthBuffer.size() - 1];
				break;
			}
			case enum_field_types::MYSQL_TYPE_FLOAT:
			{
				Result->m_resultBindBuffer.resize(Result->m_resultBindBuffer.size() + sizeof(float));
				ResultBind.buffer_type = enum_field_types::MYSQL_TYPE_FLOAT;
				ResultBind.buffer = &Result->m_resultBindBuffer[BufferStart];
				// ResultBind.buffer = new char[sizeof(int)];
				ResultBind.buffer_length = sizeof(float);
				memset(ResultBind.buffer, 0x00, sizeof(float));
				ResultBind.is_null = reinterpret_cast<bool*>(&Result->m_resultIsNullBuffer[Result->m_resultIsNullBuffer.size() - 1]);
				*ResultBind.is_null = false;
				ResultBind.length = &Result->m_resultLengthBuffer[Result->m_resultLengthBuffer.size() - 1];
				break;
			}
			default:
				ServerDebug::AssertDebugMsg("mysql result type switch error");
				break;
			}
		}

		if (0 != mysql_stmt_bind_result(m_stmtPtr, &Result->m_resultBinds[0]))
		{
			ServerDebug::AssertDebugMsg("mysql_stmt_bind_result Error" + m_DBConnecterPtr->GetLastError());
			return nullptr;
		}

	}

	// 쿼리를 날려라.
	if (0 != mysql_stmt_execute(m_stmtPtr))
	{
		m_DBConnecterPtr->GetLastError();
		return nullptr;
	}

	// 날린 결과를 받아온겁니다.
	if (0 != mysql_stmt_store_result(m_stmtPtr))
	{
		ServerDebug::AssertDebugMsg("mysql_stmt_store_result Error" + m_DBConnecterPtr->GetLastError());
		return nullptr;
	}


	// db 가 어떻게 변화됐고..
	//uint64_t Id = mysql_stmt_insert_id(m_stmtPtr);
	//// 늘어난 로우 개수를 알아올수가 있습니다.
	//// 내가 들어갈때 하나 증가한 값이 아닐수가 있습니다.
	//uint64_t Row = mysql_stmt_affected_rows(m_stmtPtr);

	// 저쪽에 들어있는 값은 
	// 내가 받아볼 값이 long

	if (nullptr != ResultMetaData)
	{
		mysql_free_result(ResultMetaData);
	}

	return Result;
	// mysql_stmt_result_metadata(m_stmtPtr);
}
