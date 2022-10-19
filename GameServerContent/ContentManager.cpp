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
	std::lock_guard lock(m_lobbyUserLock);
	m_lobbyUserTable.insert(std::make_pair(playerCharacterInfo->GetPlayerID(), UserInfo{ userEndpoint, tcpSession, playerCharacterInfo }));
}

void ContentManager::AddMatchQueue(uint64_t playerID)
{
	// match lock
	std::lock_guard<std::mutex> matchLock(m_matchLock);
	m_matchQueue.push(playerID);
	
	if (m_matchQueue.size() < m_matchCount)
		return;

	// ������ ��Ī�Ȱ��
	size_t sessionIdx = m_gameSession.size();
	GameSession newSession(m_matchCount, sessionIdx);

	for (size_t i = 0; i < m_matchCount; ++i)
	{
		// �κ������� ������ �̵���Ų��
		uint64_t playerID = m_matchQueue.front(); 
		m_matchQueue.pop();

		m_lobbyUserLock.lock();
		auto iter = m_lobbyUserTable.find(playerID);
		newSession.AddUser(iter->second);
		m_lobbyUserTable.erase(playerID);
		m_lobbyUserLock.unlock();
	}

	// ��Ī�� �����鿡�� ��ε�ĳ����
	// ������ ��Ī�� ��� ��Ī�� �����鿡�� �˸�
	// ���������� ���� �ε���, ���� ������ �ε���, �ٸ������� ���̵� ����
	newSession.BroadCastMachingPacket();

	m_sessionLock.lock();
	m_gameSession.push_back(std::move(newSession));
	m_sessionLock.unlock();
	
}


void ContentManager::BroadCastTCPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet)
{
	std::lock_guard lock(m_sessionLock);
	m_gameSession[sessionIdx].BroadCastTCP(packet);
}

void ContentManager::BroadCastUDPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession)
{
	std::lock_guard lock(m_sessionLock);
	m_gameSession[sessionIdx].BroadCastUDP(packet, udpSession);
}

void ContentManager::BroadCastUDPPlayerData(const FPlayerUpdateData& playerData, const std::shared_ptr<UDPSession>& udpSession)
{	
	std::lock_guard lock(m_sessionLock);
	m_gameSession[playerData.SessionIdx].BroadCastUDPPlayerData(playerData, udpSession);
}

