#include "pch.h"
#include <crtdbg.h>

#include <GameServerApp/ServerApp.h>

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// IOCP bind �Լ� �׽�Ʈ
	// ���ε� �ϰ� �ٽ� ���ε��Ҷ� �����۵�?
	// ���ε�� iocp�� ���� �񵿱� ó�� �Ѵ� ����?
	// -> IOCP�Ҹ��ڿ��� ������ �����Լ� ȣ�� ����?

	// ServerQueue�� ���ε� �Լ� �̸�?

	ServerApp::Start();

	return 0;
}
