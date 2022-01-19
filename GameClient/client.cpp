#include "pch.h"
#include <iostream>
#include <GameServerBase/ServerDebug.h>

#pragma comment (lib, "GameServerBase.lib")


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

	std::cout << "IP주소를 입력해주세요" << std::endl;
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

	std::cout << "커넥트 성공." << std::endl;

	// RecvThread = std::thread(RecvFunc, SessionSocket);

	//while (true)
	//{
	//	std::string In;
	//	std::cin >> In;
	//	char Buffer[1024] = { "cccc" };

	//	Sleep(1);

	//	memcpy_s(Buffer, sizeof(Buffer), In.c_str(), In.size());

	//	int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);
	//}

	_getch();

	return 0;
}
