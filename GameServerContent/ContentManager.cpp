#include "pch.h"
#include "ContentManager.h"
#include "PacketHeader.h"
#include "ServerSerializer.h"

ContentManager* ContentManager::Inst = new ContentManager;

void ContentManager::Init()
{
}

ContentManager::ContentManager()
	: m_matchCount(2)
{
}

ContentManager::~ContentManager()
{
}



void ContentManager::AddUserToLobby(const std::shared_ptr<ClientPlayer>& playerCharacterInfo, const IPEndPoint& userEndpoint, const std::shared_ptr<TCPSession>& tcpSession)
{
	std::lock_guard lock(m_lobbyLock);
	m_lobbyUserTable.insert(std::make_pair(playerCharacterInfo->GetPlayerID(), UserInfo{ userEndpoint, tcpSession, playerCharacterInfo }));
}

void ContentManager::AddMatchQueue(uint64_t playerID)
{
	std::lock_guard lock(m_lobbyLock);
	m_matchQueue.push(playerID);

	// 게임이 매칭된경우
	if (m_matchQueue.size() == m_matchCount)
	{
		// 새로운 게임 세션을 만들고
		size_t sessionIdx = m_gameSession.size();
		GameSession newSession(m_matchCount, sessionIdx);

		for (size_t i = 0; i < m_matchCount; ++i)
		{
			// 로비유저의 정보를 이동시킨다
			uint64_t playerID = m_matchQueue.front(); m_matchQueue.pop();
			auto iter = m_lobbyUserTable.find(playerID);
			newSession.AddUser(iter->second);
			m_lobbyUserTable.erase(playerID);
		}

		// 매칭된 유저들에게 브로드캐스팅
		// 게임이 매칭된 경우 매칭한 유저들에게 알림
		// 열린게임의 세션 인덱스, 현재 유저의 인덱스, 다른유저의 아이디 전달
		newSession.BroadCastMachingPacket();

		m_gameSession.push_back(std::move(newSession));
	}
}


void ContentManager::BroadCastTCPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet)
{
	m_gameSession[sessionIdx].BroadCastTCP(packet);
}

void ContentManager::BroadCastUDPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession)
{
	m_gameSession[sessionIdx].BroadCastUDP(packet, udpSession);
}

void ContentManager::BroadCastUDPPlayerData(const FPlayerUpdateData& playerData, const std::shared_ptr<UDPSession>& udpSession)
{	
	// 세션안에서 락을 걸어 처리
	m_gameSession[playerData.SessionIdx].BroadCastUDPPlayerData(playerData, udpSession);
}

