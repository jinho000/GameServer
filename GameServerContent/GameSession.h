#pragma once
#include "ServerStruct.h"

// 게임을 진행할 세션
class ServerPacketBase;
class GameSession
{
	friend class ContentManager;
private: // member var
	std::mutex				m_userInfoLock;
	std::vector<UserInfo>	m_userInfo;		// session이 들고있는 유저의 정보
	size_t					m_sessionIdx;	// session의 인덱스 번호

public: // default
	GameSession(UINT userCount, size_t sessionIdx);
	~GameSession();

	// (contentmanager vector)
	GameSession(const GameSession& other);
	GameSession(GameSession&& other) noexcept;
	GameSession& operator=(const GameSession& other);
	GameSession& operator=(GameSession&& other) noexcept;

private:
	// ContentManger에서 락을 걸고 실행하는 함수

	// 유저 추가
	void AddUser(const UserInfo& userInfo);
	
	// 클라이언트에게 matching packet 전달
	void BroadCastMachingPacket();

	// 플레이어 데이터 저장
	void SetPlayerData(const FPlayerUpdateData& playerData);

public: // member Func
	void BroadCastTCP(const std::shared_ptr<ServerPacketBase>& packet);
	void BroadCastUDP(const std::shared_ptr<ServerPacketBase>& packet, const std::shared_ptr<UDPSession>& udpSession);

	void BroadCastUDPPlayerData(const FPlayerUpdateData& playerData, const std::shared_ptr<UDPSession>& udpSession);
};

