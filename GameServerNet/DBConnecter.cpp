#include "pch.h"
#include "DBConnecter.h"
#include <mysql\mysql.h>

#include <GameServerBase/ServerDebug.h>

DBConnecter::DBConnecter()
	: m_mysqlPtr(nullptr)
{
}

DBConnecter::~DBConnecter()
{
	mysql_close(m_mysqlPtr);
	mysql_thread_end();
}

bool DBConnecter::Connect(const std::string _Host, const std::string _Id, const std::string _Pw, const std::string _Schema, unsigned int _Port)
{
	// 이미 연결한 경우
	if (nullptr != m_mysqlPtr)
	{
		return false;
	}

	// 디폴트 init
	m_mysqlPtr = mysql_init(nullptr);
	
	if (nullptr == m_mysqlPtr)
	{
		ServerDebug::AssertDebugMsg("Mysql Init Error");
		return false;
	}

	mysql_options(m_mysqlPtr, MYSQL_SET_CHARSET_NAME, "utf8");

	// 동시에 여러개의 SELECT정보를 받아볼수 있게 처리해줍니다.
	MYSQL* Handle = mysql_real_connect(m_mysqlPtr, _Host.c_str(), _Id.c_str(), _Pw.c_str(), _Schema.c_str(), 3306, nullptr, CLIENT_MULTI_RESULTS);

	if (m_mysqlPtr != Handle)
	{
		// 실패했을때 왜 실패했는지 알려줍니다.
		const char* Error = mysql_error(m_mysqlPtr);
		ServerDebug::AssertDebugMsg(std::string("Mysql connect Error =>") + Error);
		return false;
	}

	// 만약 DB와의 연결이 끊어지면
	// 자동옵션으로 핸들 내부에서 알아서 연결을 복구한다.
	bool reconnect = true;
	// 시간 1분정도 DB가 
	mysql_options(m_mysqlPtr, MYSQL_OPT_RECONNECT, &reconnect);

	// 내가 직접해도 되죠?

	 //이 헤더안의 구현내용이 알아서 쿼리 앞뒤에 mysql 서버에 보내는 프로토콜을 만들어서 
	 //날려줄거니까.
	 //함수만 열심히 찾으면 됩니다.
	 //mysql_query(Handle, "SELECT * FROM userver2.character");

	//mysql_library_end();
	//mysql_close(m_mysqlPtr);

	return true;
}

// 스테이트먼트 제작
// 스테이트먼트는 내가 넣으려는 인자값을 mysql라이브러리 
// 수준에서 방어하고 싶을때 사용하는
// 쿼리 형식이다.
std::unique_ptr<DBStatement> DBConnecter::CreateStmt(std::string_view _Query)
{
	// 프레그먼트 쿼리를 보내기 위한것으로 다이나믹 쿼리라면 이걸 만들필요가 없다.
	MYSQL_STMT* stmt = mysql_stmt_init(m_mysqlPtr);

	if (nullptr == stmt)
	{
		ServerDebug::AssertDebugMsg("mysql Statememnt Create Error");
		return nullptr;
	}

	int result = mysql_stmt_prepare(stmt, _Query.data(), static_cast<unsigned long>(_Query.length()));
	if (0 != result)
	{
		mysql_stmt_close(stmt);
		std::string err = mysql_error(m_mysqlPtr);
		ServerDebug::AssertDebugMsg("mysql Statememnt mysql_stmt_prepare Error");
		return nullptr;
	}

	return std::make_unique<DBStatement>(this, stmt, _Query);
}

std::string DBConnecter::GetLastError()
{
	return mysql_error(m_mysqlPtr);
}

