#include "pch.h"
#include "User.h"
#include <GameServerContent/PacketHeader.h>
#include <GameServerContent/ServerSerializer.h>

User::User(const std::string& _serverIP, int _serverPort)
	: m_clientSocket(_serverIP, _serverPort)
{
}

User::~User()
{
}

void User::ConnectServer()
{
	m_clientSocket.ConnectServer();
}

void User::Disconnect()
{
	m_clientSocket.DisconnectServer();
}

void User::Login(const std::string& _ID, const std::string& _PW)
{
	LoginPacket packet;
	packet.ID = _ID;
	packet.PW = _PW;

	m_clientSocket.Send(packet);
}

