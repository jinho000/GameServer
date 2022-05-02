#include "pch.h"
#include "GameSessionManager.h"

GameSessionManager* GameSessionManager::Inst = new GameSessionManager();

GameSessionManager::GameSessionManager()
	: m_gameSessionArry()
{
}

GameSessionManager::~GameSessionManager()
{
}

void GameSessionManager::InsertUser(EGameSession _gameSessionType, PtrSTCPSession _tcpSession)
{
	std::lock_guard lockGuard(m_mutex);
	m_gameSessionArry[static_cast<int>(_gameSessionType)].InsertUser(_tcpSession);

}

void GameSessionManager::BroadCast(EGameSession _gameSessionType, ServerPacketBase* _packet)
{
	std::lock_guard lockGuard(m_mutex);
	m_gameSessionArry[static_cast<int>(_gameSessionType)].BroadCast(_packet);
}

