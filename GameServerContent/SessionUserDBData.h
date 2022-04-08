#pragma once
#include "UserTable.h"
#include <GameServerBase/ServerBaseObject.h>
#include "ContentStruct.h"

// SessionUserData

// 세션이 들고있는 유저의 DB데이터
// 유저의 캐릭터 정보를 받기위해 세션에 정보 저장
// 세션에 유저 정보를 미리 받아놓는다
// (유저정보가 필요할때 디비에 갔다올필요가 없다)
// (서버의 정보와 디비의 정보를 계속 동기화시켜줘야한다)
class SessionUserDBData : public ServerBaseObject
{
public: // member var
	std::shared_ptr<UserRow> UserInfo;
	std::vector<FCharacterInfo> UserCharacterList;

public: // default
	SessionUserDBData();
	~SessionUserDBData();

	SessionUserDBData(const SessionUserDBData& _other) = delete;
	SessionUserDBData(SessionUserDBData&& _other) = delete;
	SessionUserDBData& operator=(const SessionUserDBData& _other) = delete;
	SessionUserDBData& operator=(const SessionUserDBData&& _other) = delete;

public: // member Func

	// 검증한 캐릭터의 인덱스반환
	// 실패시 -1 반환
	size_t CheckNickName(const std::string& _nickName);

	// 세션이가지고있는 캐릭터리스트에서 삭제
	void DeleteCharacter(const std::string& _nickName);

	const FCharacterInfo& GetCharacter(const std::string& _nickName);
};

