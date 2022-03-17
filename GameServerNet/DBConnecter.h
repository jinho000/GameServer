#pragma once

// 용도 :
// 분류 :
// 첨언 :
struct MYSQL;
class DBConnecter
{
private: // member var
	MYSQL* mysql_;

public: // default
	DBConnecter();
	~DBConnecter();

	DBConnecter(const DBConnecter& _other) = delete;
	DBConnecter(DBConnecter&& _other) = delete;

protected:
	DBConnecter& operator=(const DBConnecter& _other) = delete;
	DBConnecter& operator=(const DBConnecter&& _other) = delete;

private:

public: // member Func
	void Connect(
		const std::string _Host,
		const std::string _Id,
		const std::string _Pw,
		const std::string _Schema,
		unsigned int _Port
	);
};

