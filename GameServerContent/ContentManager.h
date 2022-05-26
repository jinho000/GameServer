#pragma once
#include "GameSession.h"
#include "ServerStruct.h"
#include "ClientPlayer.h"

// 로비 -> 참가요청(10) -> 세션1(10); <-> ::
// 게임내의 컨텐츠를 관리하는 매니저
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

public: // member Func

	// 유저를 로비에 추가 및 저장
	void AddUserToLobby(const std::shared_ptr<ClientPlayer>& playerCharacterInfo, const IPEndPoint& userEndpoint, const std::shared_ptr<TCPSession>& tcpSession);

	// 유저의 매칭요청을 처리
	// 게임이 매칭된경우 gameSession에 매칭된 유저 전달
	void AddMatchQueue(uint64_t playerID);

	
	// 전달받은 세션번호로 패킷 브로드캐스팅
	void BroadCastTCPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet);
	void BroadCastUDPInSession(int sessionIdx, const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession);

	// 세션안의 플레이어 데이터 브로드캐스팅
	void BroadCastUDPPlayerData(const FPlayerUpdateData& playerData, const std::shared_ptr<UDPSession>& udpSession);
};

