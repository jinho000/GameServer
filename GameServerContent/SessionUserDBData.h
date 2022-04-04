#pragma once
#include "UserTable.h"
#include <GameServerBase/ServerBaseObject.h>


class SessionUserDBData : public ServerBaseObject
{
public: // member var
	std::shared_ptr<UserRow> UserInfo;

public: // default
	SessionUserDBData();
	~SessionUserDBData();

	SessionUserDBData(const SessionUserDBData& _other) = delete;
	SessionUserDBData(SessionUserDBData&& _other) = delete;
	SessionUserDBData& operator=(const SessionUserDBData& _other) = delete;
	SessionUserDBData& operator=(const SessionUserDBData&& _other) = delete;

public: // member Func
};

