#pragma once
#include "GameSession.h"
#include "ServerStruct.h"


// �κ� -> ������û(10) -> ����1(10); <-> ::
// ���ӳ��� �������� �����ϴ� �Ŵ���
class ServerPacketBase;
class TCPSession;
class ContentManager
{
private:
	static ContentManager* Inst;

public:
	static ContentManager* GetInst()
	{
		return Inst;
	}

	static void Init();
	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private: // member var
	std::mutex								m_lobbyLock;
	std::unordered_map<uint64_t, UserInfo>	m_lobbyUserTable;

	std::queue<uint64_t>				m_matchQueue;
	UINT								m_matchCount;

	std::vector<GameSession>			m_gameSession;

private: // default
	ContentManager();
	~ContentManager();
	ContentManager(const ContentManager& _other) = delete;
	ContentManager(ContentManager&& _other) = delete;
	ContentManager& operator=(const ContentManager& _other) = delete;
	ContentManager& operator=(const ContentManager&& _other) = delete;

private:


public: // member Func

	// ������ �κ� �߰� �� ����
	void AddUserToLobby(uint64_t playerID, const IPEndPoint& userEndpoint, const std::shared_ptr<TCPSession>& tcpSession);

	// ������ ��Ī��û�� ó��
	// ������ ��Ī�Ȱ�� gameSession�� ��Ī�� ���� ����
	void AddMatchQueue(uint64_t playerID);
	
	// ���޹��� ���ǹ�ȣ�� ��Ŷ ��ε�ĳ����
	void BroadCastTCPInSession(int sessionIdx , const std::shared_ptr<ServerPacketBase>& packet);
	void BroadCastUDPInSession(int sessionIdx , const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession);

};

