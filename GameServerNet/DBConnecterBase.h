#pragma once

// �뵵 :
// �з� :
// ÷�� :
class DBConnecterBase
{
private: // member var
	MYSQL* mysql_;

public: // default
	DBConnecterBase();
	~DBConnecterBase();

	DBConnecterBase(const DBConnecterBase& _other) = delete;
	DBConnecterBase(DBConnecterBase&& _other) = delete;

protected:
	DBConnecterBase& operator=(const DBConnecterBase& _other) = delete;
	DBConnecterBase& operator=(const DBConnecterBase&& _other) = delete;

private:

public: // member Func

};

