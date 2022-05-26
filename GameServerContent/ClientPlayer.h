#pragma once
#include "ContentStruct.h"

// 용도 :
// 분류 :
// 첨언 :
class ClientPlayer
{
private: // member var
	static uint64_t PlayerID;
	FPlayerUpdateData m_playerData;

public: // default
	ClientPlayer();
	~ClientPlayer();

	ClientPlayer(const ClientPlayer& _other) = delete;
	ClientPlayer(ClientPlayer&& _other) = delete;
	ClientPlayer& operator=(const ClientPlayer& _other) = delete;
	ClientPlayer& operator=(const ClientPlayer&& _other) = delete;

public: // member Func
	void SetPos(const FVector4& pos);
	void SetRotate(const FVector4& rotate);
	void SetDir(const FVector4& dir);
	
	void SetSessionIdx(uint64_t sessionIdx);
	void SetPlayerIdx(uint64_t playerIdx);
	void SetPlayerData(const FPlayerUpdateData& playerUpdateData);

	uint64_t GetPlayerID() const { return m_playerData.PlayerID; }
	const FPlayerUpdateData& GetPlayerData() { return m_playerData; }
};

