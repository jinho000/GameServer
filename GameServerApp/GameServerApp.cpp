#include <iostream>
#include <crtdbg.h>
#include <GameServerContent/pch.h>
#include <GameServerContent/ContentCore.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ServerCore::Start<ContentCore>();
    

    return 0;
}

