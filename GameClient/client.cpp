#include "pch.h"
#include <iostream>
#include <GameServerBase/ServerDebug.h>
#include <GameServerNet/ServerHelper.h>

#pragma comment (lib, "GameServerBase.lib")
#pragma comment (lib, "GameServerNet.lib")

bool end = false;
void RecvFunc(SOCKET _sessionSocket)
{
	std::cout << "start Recv thread" << std::endl;

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

int ConnectServer()
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

	std::string IP = "127.0.0.1";
	int port = 30001;
	std::cout << "서버 접속 IP: " << IP << "Port: " << port << std::endl;

	SOCKADDR_IN Add = { 0, };
	Add.sin_family = AF_INET;
	Add.sin_port = htons(port);
	if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &Add.sin_addr))
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

}

void Input()
{
	std::string input;
	int integer = 0;
	while (true)
	{
		std::cin >> integer;

		if (true == std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}

		std::cout << integer << "\n";
	}

}


int main()
{
	_getch();

	ConnectServer();
	// 서버에 접속합니다
	// 접속 서버 IP: ~~~

	return 0;
}
