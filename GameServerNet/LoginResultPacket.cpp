#include "pch.h"
#include "LoginResultPacket.h"

LoginResultPacket::LoginResultPacket(EResultCode _eResultCode)
	: ServerPacketBase(PacketType::LOGIN_RESULT)
	, m_resultCode(_eResultCode)
{
}

LoginResultPacket::~LoginResultPacket()
{
}


void LoginResultPacket::Serialize(ServerSerializer& _serializer)
{
	int value;

	value = static_cast<int>(m_packetType);
	_serializer << value;
	
	value = static_cast<int>(m_resultCode);
	_serializer << value;
}
