#include "LoginPacket.h"

LoginPacket::LoginPacket()
	: ClientPacketBase(PacketType::LOGIN)
{
}

LoginPacket::LoginPacket(const FString& _id, const FString& _password)
	: ClientPacketBase(PacketType::LOGIN)
	, m_id(FTCHARToUTF8(*_id).Get())
	, m_password(FTCHARToUTF8(*_password).Get())
{

}

LoginPacket::~LoginPacket()
{
}

void LoginPacket::Serialize(ClientSerializer& _serializer)
{
	_serializer << static_cast<int>(m_packetType);
	_serializer << m_id;
	_serializer << m_password;
}

void LoginPacket::Deserialize(ClientSerializer& _serializer)
{
	int type;
	_serializer >> type;
	m_packetType = (PacketType)type;

	_serializer >> m_id;
	_serializer >> m_password;
}

