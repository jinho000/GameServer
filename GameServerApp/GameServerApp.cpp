#include <crtdbg.h>
#include <GameServerContent/pch.h>
#include <GameServerContent/ContentCore.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(52328);

    ServerCore::Start<ContentCore>();

    mysql_library_end();

    return 0;
}
