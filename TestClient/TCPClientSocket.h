#pragma once
#include <GameServerContent/PacketHeader.h>

class TCPClientSocket
{
private: // member var
	SOCKET		m_socket;
	bool		m_bConnect;
	std::thread m_recvThread;

	int			m_serverPort;
	std::string	m_serverIP;
	SOCKADDR_IN m_serverAddress;

public: // default
	TCPClientSocket(const std::string& _serverIP, int _serverPort);
	~TCPClientSocket();

private:
	void CloseSocket();
	void RecvThread();

public: // member Func
	void ConnectServer();
	void DisconnectServer();
	void Send(ServerPacketBase& _packet);

};

