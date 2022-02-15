#include "LoginResultPacket.h"

LoginResultPacket::LoginResultPacket()
	: ClientPacketBase(PacketType::LOGIN_RESULT)
	, m_resultCode(EResultCode::NONE)
{
}

LoginResultPacket::~LoginResultPacket()
{
}

void LoginResultPacket::Serialize(ClientSerializer& _serializer)
{
	int value;

	value = static_cast<int>(m_packetType);
	_serializer << value;

	value = static_cast<int>(m_resultCode);
	_serializer << value;
}

void LoginResultPacket::Deserialize(ClientSerializer& _serializer)
{

	int value;
	_serializer >> value;
	m_packetType = static_cast<PacketType>(value);

	_serializer >> value;
	m_resultCode = static_cast<EResultCode>(value);
}

