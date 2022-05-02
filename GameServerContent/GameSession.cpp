#include "pch.h"
#include "GameSession.h"
#include <GameServerNet/TCPSession.h>
#include "ServerSerializer.h"
#include "ServerPacketBase.h"

GameSession::GameSession()
{
	m_userSessionArry.reserve(1024);
}

GameSession::~GameSession()
{
}

void GameSession::InsertUser(PtrSTCPSession _tcpSession)
{
	m_userSessionArry.push_back(_tcpSession);
}

void GameSession::BroadCast(ServerPacketBase* _packet)
{
	for (auto tcpSession : m_userSessionArry)
	{
		ServerSerializer sr;
		(*_packet) >> sr;
		tcpSession->Send(sr.GetBuffer());
	}
}
