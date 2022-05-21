#include "pch.h"
#include "ClientPlayer.h"

uint64_t ClientPlayer::PlayerID = 1;

ClientPlayer::ClientPlayer()
	: m_playerData()
{
	m_playerData.PlayerID = PlayerID;
	++PlayerID;
}

ClientPlayer::~ClientPlayer()
{
}

void ClientPlayer::SetPos(const FVector4& _pos)
{
	m_playerData.Pos = _pos;
}

void ClientPlayer::SetRotate(const FVector4& _rotate)
{
	m_playerData.Rot = _rotate;
}

void ClientPlayer::SetDir(const FVector4& _dir)
{
	m_playerData.Dir = _dir;
}

void ClientPlayer::SetPlayerData(const FPlayerUpdateData& _playerUpdateData)
{
	m_playerData = _playerUpdateData;
}
