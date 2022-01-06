#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h> // inet_pton 함수 헤더

#pragma comment(lib, "ws2_32") 

// 네트워크 프로그래밍
// 네트워크로 연결된 프로그램끼리 통신가능하게 하는 프로그래밍
// 
// 소켓
// 운영체제에서 네트워크 통신을 지원하는 인터페이스
// 
// IP(Internet Protocol)
// 네트워크상에서 컴퓨터가 통신하기위한 주소값
// 주소값은 고유하게 부여받으며 이 주소값을 통해 데이터를 전달받거나 보낼 수 있음
// 
// Port
// 한 컴퓨터 안에서 통신을 위해 프로그램을 구별하기 위한 번호
// IP주소값은 하나의 컴퓨터에 대한 주소값이며, 한 컴퓨터 안의 프로그램중에서 어떤 프로그램과 통신할지 구별하기 위해 사용함
//
//
//
int main()
{
	WSADATA wsa;

	// 윈도우 소켓통신 시작 함수
	// MAKEWORD(2, 2): 소켓통신 버전 설정(2.2 버전)
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartup Error" << std::endl;
		return 0;
	}

	std::cout << "소켓 생성" << std::endl;

	// 소켓 생성(tcp, 연결지속방식 소켓)
	SOCKET sessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sessionSocket)
	{
		std::cout << "create socket Error" << std::endl;
		return 0;
	}

	// 연결할 소켓에 대한 정보 생성
	// 소켓통신을 위해 주소정보를 담는 구조체
	// 소켓통신을 하기 위해 포트, 프로토콜, IPv4 주소값 설정
	UINT portNumber = 40001;
	ADDRESS_FAMILY addFamily = AF_INET;
	std::string socketLocalAddr = "127.0.0.1";
	SOCKADDR_IN sockAddrIn = { 0, };
	sockAddrIn.sin_family = addFamily; // IPv4 주소체계 사용
	sockAddrIn.sin_port = htons(portNumber); // 포트 번호 설정
	if (SOCKET_ERROR == inet_pton(addFamily, socketLocalAddr.c_str(), &sockAddrIn.sin_addr))
	{
		std::cout << "inet_pton Error" << std::endl;
		return 0;
	}

	// 서버 연결 요청함수
	int len = sizeof(SOCKADDR_IN);
	if (SOCKET_ERROR == connect(sessionSocket, (const sockaddr*)&sockAddrIn, len))
	{
		std::cout << "socket connet error" << std::endl;
		return 0;
	}

	std::cout << "접속에 성공했습니다." << std::endl;

	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == "q" || input == "Q")
		{
			break;
		}
		else
		{
			char buff[512] = { 0, };
			memcpy_s(buff, sizeof(buff), input.c_str(), input.size());
			int result = send(sessionSocket, buff, sizeof(buff), 0);
		}
	}


	// 소켓 종료함수
	closesocket(sessionSocket);

	// 소켓라이브러리 종료함수
	WSACleanup();
}

