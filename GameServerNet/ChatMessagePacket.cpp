#include "pch.h"
#include "ChatMessagePacket.h"

ChatMessagePacket::ChatMessagePacket()
	: ServerPacketBase(PacketType::CHAT_MESSAGE)
{
}

ChatMessagePacket::~ChatMessagePacket()
{
}

void ChatMessagePacket::Serialize(ServerSerializer& _serializer)
{
	_serializer << static_cast<int>(m_packetType);
	_serializer << m_userID;
	_serializer << m_chatMessage;
}

void ChatMessagePacket::Deserialize(ServerSerializer& _serializer)
{
	int type;
	_serializer >> type;
	m_packetType = (PacketType)type;

	_serializer >> m_userID;
	_serializer >> m_chatMessage;
}
