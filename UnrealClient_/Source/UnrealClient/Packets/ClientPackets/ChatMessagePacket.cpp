#include "ChatMessagePacket.h"
#include "PacketType.h"


ChatMessagePacket::ChatMessagePacket()
	: ClientPacketBase(PacketType::CHAT_MESSAGE)
{
}

ChatMessagePacket::ChatMessagePacket(const FString& _userID, const FString& _ChatMessage)
	: ClientPacketBase(PacketType::CHAT_MESSAGE)
	, m_userID(FTCHARToUTF8(*_userID).Get())
	, m_ChatMessage(FTCHARToUTF8(*_ChatMessage).Get())
{
}

ChatMessagePacket::~ChatMessagePacket()
{
}

void ChatMessagePacket::Serialize(ClientSerializer& _serializer)
{
	_serializer << static_cast<int>(m_packetType);
	_serializer << m_userID;
	_serializer << m_ChatMessage;
}

void ChatMessagePacket::Deserialize(ClientSerializer& _serializer)
{
	int type;
	_serializer >> type;
	m_packetType = (PacketType)type;

	_serializer >> m_userID;
	_serializer >> m_ChatMessage;
}

