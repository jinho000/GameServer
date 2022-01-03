#include "pch.h"
#include "ServerDebug.h"
#include <cassert>

ServerDebug::ServerDebug()
{
}

ServerDebug::~ServerDebug()
{
}

ServerDebug::ServerDebug(ServerDebug&& _other) noexcept
{
}

void ServerDebug::AssertDebug()
{
	assert(false);
}

void ServerDebug::AssertDebugMsg(const std::string& _msg)
{
	MessageBoxA(nullptr, _msg.c_str(), "Debug Error", MB_OK);
	AssertDebug();
}
