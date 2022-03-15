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
	// ����Ʈ init
	mysql_ = mysql_init(nullptr);

	if (nullptr == mysql_)
	{
		ServerDebug::AssertDebugMsg("Mysql Init Error");
		return;
	}

	mysql_options(mysql_, MYSQL_SET_CHARSET_NAME, "utf8");

	// ���ÿ� �������� SELECT������ �޾ƺ��� �ְ� ó�����ݴϴ�.
	MYSQL* Handle = mysql_real_connect(mysql_, _Host.c_str(), _Id.c_str(), _Pw.c_str(), _Schema.c_str(), 3306, nullptr, CLIENT_MULTI_RESULTS);

	if (mysql_ != Handle)
	{
		// ���������� �� �����ߴ��� �˷��ݴϴ�.
		const char* Error = mysql_error(mysql_);
		ServerDebug::AssertDebugMsg(std::string("Mysql connect Error =>") + Error);
		return;
	}

	// ���� DB���� ������ ��������
	// �ڵ��ɼ����� �ڵ� ���ο��� �˾Ƽ� ������ �����Ѵ�.
	bool reconnect = true;
	// �ð� 1������ DB�� 
	mysql_options(mysql_, MYSQL_OPT_RECONNECT, &reconnect);
	// ���� �����ص� ����?

	 //�� ������� ���������� �˾Ƽ� ���� �յڿ� mysql ������ ������ ���������� ���� 
	 //�����ٰŴϱ�.
	 //�Լ��� ������ ã���� �˴ϴ�.
	 //mysql_query(Handle, "SELECT * FROM userver2.character");

}


