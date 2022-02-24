#include "ClientPacketBase.h"

ClientPacketBase::ClientPacketBase(PacketType _packetType)
	: m_packetType(_packetType)
{
}

ClientPacketBase::~ClientPacketBase()
{
}
