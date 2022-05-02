#pragma once
#include "GameSession.h"
#include "ContentEnum.h"

// 용도 :
// 분류 :
// 첨언 :
class ServerPacketBase;
class GameSessionManager
{
private: // member var
	static GameSessionManager* Inst;

public:
	static GameSessionManager* GetInst()
	{
		return Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:
	std::mutex m_mutex;
	GameSession m_gameSessionArry[static_cast<int>(EGameSession::COUNT)];

private: // default
	GameSessionManager();
	~GameSessionManager();

	GameSessionManager(const GameSessionManager& _other) = delete;
	GameSessionManager(GameSessionManager&& _other) = delete;
	GameSessionManager& operator=(const GameSessionManager& _other) = delete;
	GameSessionManager& operator=(const GameSessionManager&& _other) = delete;

public: // member Func
	void InsertUser(EGameSession _gameSessionType, PtrSTCPSession _tcpSession);
	void BroadCast(EGameSession _gameSessionType, ServerPacketBase* _packet);
};

