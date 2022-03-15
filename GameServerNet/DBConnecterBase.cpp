#include "pch.h"
#include "DBConnecterBase.h"
#include <mysql\mysql.h>


DBConnecterBase::DBConnecterBase()
	: mysql_(nullptr)
{
}

DBConnecterBase::~DBConnecterBase()
{
}

void DBConnecterBase::Connect(const std::string _Host, const std::string _Id, const std::string _Pw, const std::string _Schema, unsigned int _Port)
{
	// 디폴트 init
	mysql_ = mysql_init(nullptr);

	if (nullptr == mysql_)
	{
		ServerDebug::AssertDebugMsg("Mysql Init Error");
		return;
	}

	mysql_options(mysql_, MYSQL_SET_CHARSET_NAME, "utf8");

	// 동시에 여러개의 SELECT정보를 받아볼수 있게 처리해줍니다.
	MYSQL* Handle = mysql_real_connect(mysql_, _Host.c_str(), _Id.c_str(), _Pw.c_str(), _Schema.c_str(), 3306, nullptr, CLIENT_MULTI_RESULTS);

	if (mysql_ != Handle)
	{
		// 실패했을때 왜 실패했는지 알려줍니다.
		const char* Error = mysql_error(mysql_);
		ServerDebug::AssertDebugMsg(std::string("Mysql connect Error =>") + Error);
		return;
	}

	// 만약 DB와의 연결이 끊어지면
	// 자동옵션으로 핸들 내부에서 알아서 연결을 복구한다.
	bool reconnect = true;
	// 시간 1분정도 DB가 
	mysql_options(mysql_, MYSQL_OPT_RECONNECT, &reconnect);
	// 내가 직접해도 되죠?

	 //이 헤더안의 구현내용이 알아서 쿼리 앞뒤에 mysql 서버에 보내는 프로토콜을 만들어서 
	 //날려줄거니까.
	 //함수만 열심히 찾으면 됩니다.
	 //mysql_query(Handle, "SELECT * FROM userver2.character");

}


