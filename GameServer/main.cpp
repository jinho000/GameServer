#include "pch.h"
#include "Test.h"
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ServerDebug::Initialize();

	Test::TestListener();

	ServerDebug::Destroy();

	// IOCP bind 함수 테스트
	// 바인드 하고 다시 바인드할때 정상작동?
	// 바인드된 iocp는 동기 비동기 처리 둘다 가능?
	// -> IOCP소멸자에서 스레드 종료함수 호출 가능?

	// ServerQueue의 바인드 함수 이름?


	return 0;
}
