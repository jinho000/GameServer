#pragma once
#include "UserTable.h"
#include <GameServerBase/ServerBaseObject.h>

class ContentUserData : public ServerBaseObject
{
public: // member var
	std::shared_ptr<UserRow> userData;

public: // default
	ContentUserData();
	~ContentUserData();

	ContentUserData(const ContentUserData& _other) = delete;
	ContentUserData(ContentUserData&& _other) = delete;
	ContentUserData& operator=(const ContentUserData& _other) = delete;
	ContentUserData& operator=(const ContentUserData&& _other) = delete;

public: // member Func
};

