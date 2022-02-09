#include "pch.h"
#include "ServerPacketBase.h"

ServerPacketBase::ServerPacketBase(PacketType _packetType)
	: m_packetType(_packetType)
{
}

ServerPacketBase::~ServerPacketBase()
{
}

void ServerPacketBase::operator>>(ServerSerializer& _serializer)
{
	Serialize(_serializer);
}

void ServerPacketBase::operator<<(ServerSerializer& _serializer)
{
	Deserialize(_serializer);
}

