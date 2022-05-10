#include <iostream>
#include <cassert>
#include <GameServerBase/pch.h>
#include <GameServerBase/ServerQueue.h>
#include <functional>


SOCKADDR_IN sockAddrIn = { 0, };

SOCKET CreateUDPSocket()
{
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (INVALID_SOCKET == udpSocket)
	{
		std::cout << "create socket Error" << std::endl;
		assert(nullptr);
		return 0;
	}

    return udpSocket;
}

std::mutex sockAddrMutex;

void ThreadWork(SOCKET _clientSocket)
{

	
	sockAddrMutex.lock();
	std::cout << _clientSocket << std::endl;
	int len = sizeof(SOCKADDR_IN);
	if (SOCKET_ERROR == connect(_clientSocket, (const sockaddr*)&sockAddrIn, len))
	{
		std::cout << "socket connet error" << std::endl;
	}
	sockAddrMutex.unlock();

	std::string input = "AAAAA";
	char buff[512] = { 0, };
	memcpy_s(buff, sizeof(buff), input.c_str(), input.size());
	int result = send(_clientSocket, buff, sizeof(buff), 0);
}

int main()
{
	// 라이브러리 초기화
	{
		WSADATA wsa;
		if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		{
			std::cout << "WSAStartup Error" << std::endl;
			return 0;
		}
	}

	// 서버의 주소값 생성
	{
		UINT portNumber = 30002;	// 접속할 서버의 포트
		ADDRESS_FAMILY addFamily = AF_INET; // 접속할 서버의 주소체계
		std::string socketLocalAddr = "127.0.0.1";// 접속할 서버의 IP

		sockAddrIn.sin_family = addFamily; // IPv4 주소체계 사용
		sockAddrIn.sin_port = htons(portNumber); // 포트 번호 설정
		if (SOCKET_ERROR == inet_pton(addFamily, socketLocalAddr.c_str(), &sockAddrIn.sin_addr))
		{
			std::cout << "inet_pton Error" << std::endl;
			return 0;
		}
	}

	// 소켓 생성
	const UINT socketCount = 150;
	SOCKET testSockeyArry[socketCount] = {};
	for (int i = 0; i < socketCount; ++i)
	{
		testSockeyArry[i] = CreateUDPSocket();
	}

	// 테스트 시작
	ServerQueue jobQueue;
	jobQueue.Initialize(socketCount);

	for (int i = 0; i < socketCount; ++i)
	{
		jobQueue.Enqueue(std::bind(ThreadWork, testSockeyArry[i]));
	}

	jobQueue.Destroy();

	for (int i = 0; i < socketCount; ++i)
	{
		closesocket(testSockeyArry[i]);
	}
    return 0;
}

