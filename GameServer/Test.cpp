#include "pch.h"
#include "Test.h"

#include <iostream>
#include <unordered_map>
#include <conio.h>
#include <functional>

#include <GameServerBase/ServerIOCP.h>
#include <GameServerBase/ServerIOCPWorker.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerBase/ServerQueue.h>
#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerBase/ServerString.h>
#include <GameServerNet/ServerSerializer.h>
#include <GameServerNet/ServerPacketBase.h>
#include <GameServerNet/LoginPacket.h>
#include <GameServerNet/PacketConvertor.h>
#include <GameServerNet/PacketDispatcher.h>
#include <GameServerNet/LoginPacketHandler.h>

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

    std::string ip = "127.0.0.1"; // ������ �ּ�
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


    std::cout << "���� ���� �Լ� ����" << std::endl;

    SOCKADDR_IN userAddrIn = { 0, }; // ����� ������ ������ ��� ����ü
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

void Test::TestRecv()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("�����ڰ� �ֽ��ϴ�");

		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _data) {
				
			}, 
			[](PtrSTCPSession _tcpSession) {

			});
		});

	_getch();
}

void Test::TestSend()
{
	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("�����ڰ� �ֽ��ϴ�");

		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _data) {
				std::string strANSI;
				std::string strUTF8(reinterpret_cast<const char*>(_data.data()));
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
				ServerDebug::LogInfo("������ ���� ����");
			});
		});

	_getch();
}

ServerQueue loginJobQeue(ServerQueue::WORK_TYPE::Default, 10, "jobQueue");

template<class PacketType, class PacketHandler> 
void ProcessHandler(PtrSTCPSession _s, PtrSPacketBase _packet)
{
	// ��Ŷ ��ȯ
	std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType> (_packet);
	assert(nullptr != packet);

	// handler ó�� ����
	std::shared_ptr<PacketHandler> handler = std::make_shared<PacketHandler>(_s, packet);
	handler->Start();
}

PacketDispatcher<TCPSession> dispatcher;

void Test::TestListener()
{
	// dispatcher�� ��Ŷ�� ó���� �Լ� �߰�
	PacketHandler<TCPSession> loginHandler = &ProcessHandler<LoginPacket, LoginPacketHandler>;
	dispatcher.AddHandler(PacketType::LOGIN, loginHandler);

	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("�����ڰ� �ֽ��ϴ�");

		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _buffer) {
				
				// ��Ŷ ó��
				PacketConvertor convertor(_buffer);
				// ��Ŷ�� ���� ó�� ���μ��� ��������
				const PacketHandler<TCPSession>& handler = dispatcher.GetHandler(convertor.GetPacketType());
				// ��Ŷ ó�� ����
				handler(_tcpSession, convertor.GetPacket());

			},
			[](PtrSTCPSession _tcpSession) {
				ServerDebug::LogInfo("������ ���� ����");
			});
		});

	_getch();
}

void Test::TestString()
{
	std::wstring unicodeStr = L"�ѱ� �׽�Ʈ";
	std::string ansiStr;
	std::string utf8Buffer;
	std::string ansiBuffer;


	ServerString::UNICODEToANSI(unicodeStr, ansiStr);
	std::cout << "ANSI String: " << ansiStr << std::endl; // ���� ����

	ServerString::ANSIToUTF8(ansiStr, utf8Buffer); // ������ ����
	ServerString::UTF8ToANSI(utf8Buffer, ansiBuffer); // ������ ����

	std::cout << "ANSI Buffer String: " << ansiBuffer << std::endl; // ���� ����
}
