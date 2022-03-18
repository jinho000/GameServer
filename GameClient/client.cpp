#include "pch.h"
#include <iostream>
#include <GameServerBase/ServerDebug.h>
#include <GameServerNet/ServerHelper.h>

#pragma comment (lib, "GameServerBase.lib")
#pragma comment (lib, "GameServerNet.lib")

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

	//std::cout << "루프백 주소로 접속" << std::endl;
	//std::string Ip = "127.0.0.1";
	//std::string Ip = "172.30.1.45";
	std::cout << "서버 접속" << std::endl;
	std::string Ip = ServerHelper::GetMyIP();

	SOCKADDR_IN Add = { 0, };
	Add.sin_family = AF_INET;
	Add.sin_port = htons(30000);
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

// 서버 테스트용 클라이언트
// 1 프로그램 시작시 로컬서버에 접속
// 1.1 접속성공시 접속성공 출력
// 1.2 접속실패시 접속실패 출력 대기 후 입력을 다시 누르면 다시 접속 시도
//
// 2 패킷처리
// 2.1 패킷 받아오기
// 2.2 패킷 보내기
// 
// 
//
int main()
{
	_getch();
	ConnectServer();
	// 서버에 접속합니다
	// 접속 서버 IP: ~~~

	return 0;
}
