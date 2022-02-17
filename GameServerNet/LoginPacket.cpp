#include "pch.h"
#include "LoginPacket.h"


LoginPacket::LoginPacket()
	: ServerPacketBase(PacketType::LOGIN)
{
}


LoginPacket::~LoginPacket()
{
}

//void LoginPacket::Serialize(ServerSerializer& _serializer)
//{
//	_serializer << static_cast<int>(m_packetType);
//	_serializer << m_id;
//	_serializer << m_password;
//}

void LoginPacket::Deserialize(ServerSerializer& _serializer)
{
	int type;
	_serializer >> type;
	m_packetType = (PacketType)type;
	
	std::string utf8ID;
	std::string utf8PW;
	_serializer >> utf8ID;
	_serializer >> utf8PW;

	ServerString::UTF8ToANSI(utf8ID, m_id);
	ServerString::UTF8ToANSI(utf8PW, m_password);
}
