#include "pch.h"
#include "Test.h"

#include <iostream>
#include <conio.h>
#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerBase/ServerQueue.h>
#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerBase/ServerString.h>

#include <GameServerNet/enum.h>

SOCKET Test::CreateSocket()
{
    WSADATA ws;
    if (0 != WSAStartup(MAKEWORD(2, 2), &ws))
    {
        std::cout << "WSAStartUp err!\n";
        return 0;
    }

    SOCKET acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == acceptSocket)
    {
        std::cout << "Socket err!\n";
        return 0;
    }

    SOCKADDR_IN sockAddrIn = { 0, };
    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_port = htons(30000);

    std::string ip = "127.0.0.1"; // 루프백 주소
    if (1 != inet_pton(AF_INET, ip.c_str(), &sockAddrIn.sin_addr))
    {
        std::cout << "(local addr)inet pton err!\n";
        return 0;
    }

    if (SOCKET_ERROR == bind(acceptSocket, (const sockaddr*)&sockAddrIn, sizeof(SOCKADDR_IN)))
    {
        std::cout << "socket bind err!\n";
        return 0;
    }

    if (SOCKET_ERROR == listen(acceptSocket, 512))
    {
        std::cout << "socket listen err!\n";
        return 0;
    }


    std::cout << "서버 접속 함수 실행" << std::endl;

    SOCKADDR_IN userAddrIn = { 0, }; // 연결된 유저의 정보를 담는 구조체
    int len = sizeof(SOCKADDR_IN);

    return acceptSocket;
}

void Test::TestServerBaseObject()
{

}

void IOCPFunc(std::shared_ptr<ServerIOCPWorker> _iocpWorker)
{
	while (true)
	{
		_iocpWorker->Wait(INFINITE);
		std::string logInfo = "test Log";
		ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		
		std::cout << "test" << std::endl;
	}
}

void Test::TestIOCP()
{
	ServerIOCP iocp(&IOCPFunc, 3);
	bool b = false;
	HANDLE hnd = (HANDLE)CreateSocket();
	b = iocp.AsyncBind(hnd, 0);

	if (b == false)
	{
		int a = 0;
	}

	b = iocp.AsyncBind(hnd, 0);

	if (b == false)
	{
		ServerDebug::GetLastErrorPrint();
		int a = 0;
	}

	_getch();
}

void testfunc()
{
	std::cout << "test " << std::endl;
}

void Test::TestServerQueue()
{
	ServerQueue serverQueue(ServerQueue::WORK_TYPE::Default, 1);
	
	serverQueue.Enqueue(testfunc);
}


void Test::TestLog()
{
	ServerIOCP iocp(&IOCPFunc, 10);

	while (true)
	{
		char c = _getch();
		if (c == 'a')
		{
			std::string logInfo = "test Log";
			ServerDebug::Log(LOG_TYPE::TYPE_INFO, logInfo);
		}
	}

}

void Test::TestListener()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession){
		ServerDebug::LogInfo("접속자가 있습니다");

	});

	_getch();
}

void Test::TestRecv()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("접속자가 있습니다");

		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<char>& _data) {
				std::string data = &_data[0];
				ServerDebug::LogInfo(data);
			}, 
			[](PtrSTCPSession _tcpSession) {

			});
		});

	_getch();
}

void Test::TestSend()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("접속자가 있습니다");

		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<char>& _data) {
				std::string strANSI;
				std::string strUTF8(_data.data());
				ServerString::UTF8ToANSI(strUTF8, strANSI);
				ServerDebug::LogInfo(strANSI);

				//data += " - server";

				//std::vector<char> buffer;
				//buffer.resize(data.length() + 1);
				//std::copy(data.begin(), data.end(), buffer.begin());
				//buffer[data.length()] = '\0';

				//_tcpSession->Send(buffer);
			},
			[](PtrSTCPSession _tcpSession) {
				ServerDebug::LogInfo("접속자 접속 종료");
			});
		});

	_getch();
}

void Test::TestString()
{
	std::wstring unicodeStr = L"한글 테스트";
	std::string ansiStr;
	std::string utf8Buffer;
	std::string ansiBuffer;


	ServerString::UNICODEToANSI(unicodeStr, ansiStr);
	std::cout << "ANSI String: " << ansiStr << std::endl; // 시작 문자

	ServerString::ANSIToUTF8(ansiStr, utf8Buffer); // 데이터 전송
	ServerString::UTF8ToANSI(utf8Buffer, ansiBuffer); // 데이터 수신

	std::cout << "ANSI Buffer String: " << ansiBuffer << std::endl; // 시작 문자
}
