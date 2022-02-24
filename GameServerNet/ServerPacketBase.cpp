#include "pch.h"
#include "ServerPacketBase.h"

ServerPacketBase::ServerPacketBase(PacketType _packetType)
	: m_packetType(_packetType)
	, m_size(-1)
{
}

ServerPacketBase::~ServerPacketBase()
{
}

