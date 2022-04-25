#include "pch.h"
#include "SessionUserDBData.h"

SessionUserDBData::SessionUserDBData()
{
}

SessionUserDBData::~SessionUserDBData()
{
}

size_t SessionUserDBData::CheckNickName(const std::string& _nickName)
{
	size_t index = -1;
	for (size_t i = 0; i < UserCharacterList.size(); i++)
	{
		if (UserCharacterList[i].NickName == _nickName)
		{
			return UserCharacterList[i].Index;
		}
	}

    return index;
}

void SessionUserDBData::DeleteCharacter(const std::string& _nickName)
{
	auto iter = UserCharacterList.begin();
	while (iter != UserCharacterList.end())
	{
		if (iter->NickName == _nickName)
		{
			UserCharacterList.erase(iter);
			return;
		}

		++iter;
	}
}

const FCharacterInfo& SessionUserDBData::GetCharacter(const std::string& _nickName)
{
	auto iter = UserCharacterList.begin();
	while (iter != UserCharacterList.end())
	{
		if (iter->NickName == _nickName)
		{
			return *iter;
		}

		++iter;
	}

	ServerDebug::AssertDebugMsg("Get Character Fail");

	return *iter;
}
