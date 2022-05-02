#pragma once

// �뵵 :
// �з� :
// ÷�� :
class TCPSession;
class ServerPacketBase;
class GameSession
{
private: // member var
	std::vector<PtrSTCPSession> m_userSessionArry;

public: // default
	GameSession();
	~GameSession();

	GameSession(const GameSession& _other) = delete;
	GameSession(GameSession&& _other) = delete;
	GameSession& operator=(const GameSession& _other) = delete;
	GameSession& operator=(const GameSession&& _other) = delete;


public: // member Func
	void InsertUser(PtrSTCPSession _tcpSession);
	void BroadCast(ServerPacketBase* _packet);
};

