#include "pch.h"
#include "Test.h"
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ServerDebug::Initialize();

	Test::TestListener();

	ServerDebug::Destroy();

	// IOCP bind �Լ� �׽�Ʈ
	// ���ε� �ϰ� �ٽ� ���ε��Ҷ� �����۵�?
	// ���ε�� iocp�� ���� �񵿱� ó�� �Ѵ� ����?
	// -> IOCP�Ҹ��ڿ��� ������ �����Լ� ȣ�� ����?

	// ServerQueue�� ���ε� �Լ� �̸�?


	return 0;
}
