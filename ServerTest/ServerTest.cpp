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
// 네트워크상에서 컴퓨타가 통신하기위한 주소값
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
	// WS232.dll의 사용을 시작 하기 위해 호출 
	// 사용할 소켓버전을 윈도우에 알리고, Windows Sockets DLL의 사용을 초기화 
	// MAKEWORD(2, 2): 소켓통신 버전 설정(2.2 버전)
	// WSADATA 구조체 주소값을 넘겨 초기화된 데이터의 정보를 받아옴


	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartup Error" << std::endl;
		return 0;
	}


	// 소켓통신을 위해 주소정보를 담는 구조체
	// 소켓통신을 하기 위해 포트, 프로토콜, IPv4 주소값 설정
	UINT portNumber = 40001;
	ADDRESS_FAMILY addFamily = AF_INET;
	std::string socketLocalAddr = "127.0.0.1";

	SOCKADDR_IN sockAddrIn = { 0, };
	sockAddrIn.sin_family = addFamily; // IPv4 주소체계 사용
	sockAddrIn.sin_port = htons(portNumber); // 포트 번호 설정
	
	// 소켓의 로컬 주소값 설정
	// IPv4 로컬 주소값을 데이터읽는 방식(리틀엔디언, 빅엔디언)에 맞게 만들어주는 함수
	if (SOCKET_ERROR == inet_pton(addFamily, socketLocalAddr.c_str(), &sockAddrIn.sin_addr))
	{
		std::cout << "inet_pton Error" << std::endl;
		return 0;
	}

	std::cout << "소켓 생성" << std::endl;

	// 소켓 생성 함수
	// (tcp, 연결지속방식 소켓)
	SOCKET acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == acceptSocket)
	{
		std::cout << "create socket Error" << std::endl;
		return 0;
	}
	
	// 소켓에 소켓통신을 위한 데이터 전달
	if (SOCKET_ERROR == bind(acceptSocket, (const sockaddr*)&sockAddrIn, sizeof(SOCKADDR_IN)))
	{
		std::cout << "socket bind Error" << std::endl;
		return 0;
	}

	// 소켓을 연결 가능한 상태로 전환
	int backlog = 512;
	if (SOCKET_ERROR == listen(acceptSocket, backlog))
	{
		std::cout << "socket listen Error" << std::endl;
		return 0;
	}
	
	// 클라이언트 요청을 받는 함수 실행
	std::cout << "서버 접속 함수 실행" << std::endl;
	SOCKADDR_IN userAddrIn = { 0, };
	int len = sizeof(SOCKADDR_IN);

	// 클라이언트 요청에 대한 소켓 반환
	SOCKET sessionSocket = accept(acceptSocket, (sockaddr*)&userAddrIn, &len);
	if (INVALID_SOCKET == sessionSocket)
	{
		std::cout << "session socket Error" << std::endl;
		return 0;
	}


	std::cout << "접속자가 있습니다" << std::endl;


	while (true)
	{
		char buff[512];
		int result = recv(sessionSocket, buff, sizeof(buff), 0);

		std::cout << buff << std::endl;

		if (std::string(buff) == "quit")
		{
			break;
		}
	}


	// 소켓 종료함수
	closesocket(sessionSocket);
	closesocket(acceptSocket);

	// 윈도우 소켓 라이브러리 사용 종료함수
	WSACleanup();
}

