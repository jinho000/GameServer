#pragma once
#include "ServerBaseObject.h"

// 용도 :
// 분류 :
// 첨언 :
class ServerNameBase : public ServerBaseObject
{
private: // member var
	std::string m_name;

public: // default
	ServerNameBase(const std::string& _name);
	~ServerNameBase();

	ServerNameBase(const ServerNameBase& _other) = delete;
	ServerNameBase(ServerNameBase&& _other) noexcept;

protected:
	ServerNameBase& operator=(const ServerNameBase& _other) = delete;
	ServerNameBase& operator=(const ServerNameBase&& _other) = delete;

private:

public: // member Func
	void SetName(const std::string& _name);

	const std::string& GetName() const;
	std::string GetNameCopy() const;
	std::string_view GetNameView() const;
	const char* GetNameChar() const;
};

