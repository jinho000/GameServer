#pragma once

// 컨텐트 패킷의 enum 이름은 항상 E로 시작해야함

enum class EResultCode
{
	NONE = -1,
	OK,
	FAIL,
	MAX
};

enum class ELoginResultCode
{
	FAIL,
	ID_ERROR,
	PW_ERROR,
	OK,
	MAX
};

enum class EJoinResultCode
{
	FAIL,
	ID_DUPLE,
	OK,
	MAX
};

enum class ECreateCharacterResultCode
{
	FAIL,
	ID_DULE,
	OK,
	MAX
};

enum class ESectionType
{
	NONE,
	NONEFIGHT,
	FIGHTZONE1,
	FIGHTZONE2,
	FIGHTZONE3,
	FIGHTZONE4,
	MAX,
};

enum class EGameSession
{
	SESSION0,
	SESSION1,
	SESSION2,
	SESSION3,
	SESSION4,
	COUNT
};
