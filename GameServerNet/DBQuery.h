#pragma once

// 용도 :
// 분류 :
// 첨언 :
class DBConnecter;
class DBQuery
{
protected: // member var
	DBConnecter*	DBConnecterPtr;
	const char*		QueryString;

public: // default
	DBQuery(const char* _Query);
	~DBQuery();

	DBQuery(const DBQuery& _other) = delete;
	DBQuery(DBQuery&& _other) = delete;
	DBQuery& operator=(const DBQuery& _other) = delete;
	DBQuery& operator=(const DBQuery&& _other) = delete;


public: // member Func
	// 이함수를 실행해야만 쿼리가 db에 날아간다.
	virtual bool DoQuery() = 0;
};

