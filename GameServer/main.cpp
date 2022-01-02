#include "pch.h"
#include <iostream>
#include <GameServerBase/GameServerDebug.h>

int main()
{
	GameServerDebug::AssertDebugMsg("debug test");

	std::cout << "test" << std::endl;
	return 0;
}
