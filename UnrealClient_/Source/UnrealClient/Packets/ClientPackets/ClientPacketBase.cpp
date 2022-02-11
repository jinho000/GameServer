#include "ClientPacketBase.h"

ClientPacketBase::ClientPacketBase(PacketType _packetType)
	: m_packetType(_packetType)
{
}

ClientPacketBase::~ClientPacketBase()
{
}

void ClientPacketBase::operator>>(ClientSerializer& _serializer)
{
	Serialize(_serializer);
}

void ClientPacketBase::operator<<(ClientSerializer& _serializer)
{
	Deserialize(_serializer);
}
