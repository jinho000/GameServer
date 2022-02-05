#include "pch.h"
#include <iostream>
#include <GameServerBase/ServerDebug.h>

#pragma comment (lib, "GameServerBase.lib")

bool end = false;
void RecvFunc(SOCKET _sessionSocket)
{
	while (false == end)
	{
		char buffer[1024];
		int result = recv(_sessionSocket, buffer, sizeof(buffer), 0);
		if (SOCKET_ERROR == result)
		{
			end = true;
			return;
		}

		std::cout << buffer << std::endl;
	}
}

int main()
{
	WSADATA wsa;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartup Error" << std::endl;
	}

	SOCKET SessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == SessionSocket)
	{
		return 0;
	}

	std::cout << "IP�ּҸ� �Է����ּ���" << std::endl;
	std::string Ip;
	std::string Port;
	std::cin >> Ip;

	if ("Q" == Ip
		|| "q" == Ip)
	{
		Ip = "127.0.0.1";
	}

	SOCKADDR_IN Add = { 0, };
	Add.sin_family = AF_INET;
	Add.sin_port = htons(30001);
	if (SOCKET_ERROR == inet_pton(AF_INET, Ip.c_str(), &Add.sin_addr))
	{
		return 0;
	}
	int Len = sizeof(SOCKADDR_IN);

	if (SOCKET_ERROR == connect(SessionSocket, (const sockaddr*)&Add, Len))
	{
		ServerDebug::GetLastErrorPrint();
		return 0;
	}

	std::cout << "Ŀ��Ʈ ����." << std::endl;

	std::thread RecvThread(RecvFunc, SessionSocket);

	while (true)
	{
		std::string In;
		std::cin >> In;
		//char buffer[1024] = { 0, };
		//memcpy_s(buffer, sizeof(buffer), In.c_str(), In.length() + 1);
		if (In == "q")
		{
			closesocket(SessionSocket);
			end = true;
			RecvThread.join();

			return 0;
		}
		int Result = send(SessionSocket, In.c_str(), In.length() + 1, 0);
	}

	_getch();

	return 0;
}