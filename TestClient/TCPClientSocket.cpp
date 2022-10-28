#include "pch.h"
#include "TCPClientSocket.h"
#include <GameServerContent/ServerSerializer.h>

TCPClientSocket::TCPClientSocket(const std::string& _serverIP, int _serverPort)
	: m_serverIP(_serverIP)
	, m_serverPort(_serverPort)
	, m_bConnect(false)
{
	// TCPClientSocket 생성
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(NULL != m_socket);

	// 서버 주소값 바인딩
	// 주소값, 포트 세팅
	m_serverAddress.sin_family = AF_INET;
	m_serverAddress.sin_port = htons(m_serverPort);
	int convertAddressResult = inet_pton(AF_INET, m_serverIP.c_str(), &m_serverAddress.sin_addr);

	assert(convertAddressResult != SOCKET_ERROR);
}

TCPClientSocket::~TCPClientSocket()
{
	CloseSocket();
}

void TCPClientSocket::CloseSocket()
{
	if (NULL != m_socket)
	{
		closesocket(m_socket);
		m_socket = NULL;
	}

	if (m_recvThread.joinable() == true)
	{
		m_recvThread.join();
	}
}

void TCPClientSocket::RecvThread()
{
	assert(m_bConnect == true);

	while (true)
	{
		char buffer[1024] = {};
		int recvResult = recv(m_socket, buffer, 1024, 0);

		if (recvResult == -1)
		{
			break;
		}


	}
}

void TCPClientSocket::ConnectServer()
{
	if (m_bConnect == true)
		return;

	int bConnect = connect(m_socket, (const sockaddr*)&m_serverAddress, sizeof(m_serverAddress));
	m_bConnect = true;
	assert(bConnect != SOCKET_ERROR);

	// 서버 설정 후 recv스레드 시작
	m_recvThread = std::thread(&TCPClientSocket::RecvThread, this);
}

void TCPClientSocket::DisconnectServer()
{
	CloseSocket();
	m_bConnect = false;
}

void TCPClientSocket::Send(ServerPacketBase& _packet)
{
	assert(m_bConnect == true);
	ServerSerializer sr;
	_packet >> sr;
	
	int sendResult = send(m_socket, (const char*)sr.GetBuffer().data(), sr.GetBuffer().size(), 0);
}
