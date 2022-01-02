#include "pch.h"
#include "GameServerDebug.h"
#include <assert.h>

GameServerDebug::GameServerDebug()
{
}

GameServerDebug::~GameServerDebug()
{
}

GameServerDebug::GameServerDebug(GameServerDebug&& _other) noexcept
{
}

void GameServerDebug::AssertDebugMsg(const std::string& msg)
{
	MessageBoxA(nullptr, msg.c_str(), "GameServer Error", MB_OK);
	assert(false);
}
