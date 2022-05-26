#include "pch.h"
#include "GameSession.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/UDPSession.h>
#include "ServerSerializer.h"
#include "ServerPacketBase.h"
#include "PacketHeader.h"


class TCPSession;
GameSession::GameSession(UINT userCount, size_t sessionIdx)
	: m_sessionIdx(sessionIdx)
{
	m_userInfo.reserve(userCount);
}

GameSession::~GameSession()
{
}

GameSession::GameSession(const GameSession& other)
	: m_sessionIdx(other.m_sessionIdx)
{
	assert(nullptr);
}

GameSession::GameSession(GameSession&& other) noexcept
	: m_userInfo(std::move(other.m_userInfo))
	, m_sessionIdx(other.m_sessionIdx)
{
}

GameSession& GameSession::operator=(const GameSession& other)
{
	assert(nullptr);
	return *this;
}


GameSession& GameSession::operator=(GameSession&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	m_userInfo = std::move(other.m_userInfo);
	m_sessionIdx = other.m_sessionIdx;

	return *this;
}

void GameSession::AddUser(const UserInfo& userInfo)
{
	// ContentManager에서 락을 걸어주므로 걸 필요없다
	m_userInfo.push_back(userInfo);
}

void GameSession::BroadCastTCP(const std::shared_ptr<ServerPacketBase>& packet)
{
	std::lock_guard lock(m_userInfoLock);
	for (UserInfo& userInfo : m_userInfo)
	{
		ServerSerializer sr;
		*packet >> sr;
		userInfo.userTCPSession->Send(sr.GetBuffer());
	}
}

void GameSession::BroadCastUDP(const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession)
{
	std::lock_guard lock(m_userInfoLock);
	for (UserInfo& userInfo : m_userInfo)
	{
		ServerSerializer sr;
		*packet >> sr;
		udpSession->Send(sr.GetBuffer(), userInfo.userEndPoint);
	}
}

void GameSession::BroadCastMachingPacket()
{
	// ContentManager에서 락을 걸어주므로 걸 필요없다
	//GameMatchPacket packet;
	//packet.sessionIdx = static_cast<int>(m_sessionIdx);

	//for (size_t i = 0; i < m_userInfo.size(); i++)
	//{
	//	packet.userIdx = static_cast<int>(i);

	//	ServerSerializer sr;
	//	packet >> sr;
	//	m_userInfo[i].userTCPSession->Send(sr.GetBuffer());
	//}
}
