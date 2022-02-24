#pragma once
#include "ServerPacketBase.h"

class ChatMessagePacket : public ServerPacketBase
{
public: // member var
	std::string m_userID;
	std::string m_chatMessage;

public: // default
	ChatMessagePacket()
		: ServerPacketBase(PacketType::CHAT_MESSAGE)
	{

	}

	~ChatMessagePacket() = default;

	ChatMessagePacket(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket(ChatMessagePacket&& _other) = delete;

protected:
	ChatMessagePacket& operator=(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket& operator=(const ChatMessagePacket&& _other) = delete;

private:

public: // member Func
	virtual int SizeCheck() override
	{
		return DataSizeCheck(m_userID) + DataSizeCheck(m_chatMessage);
	}

	void Serialize(ServerSerializer& _serializer) override
	{
		ServerPacketBase::Serialize(_serializer);

		_serializer << m_userID;
		_serializer << m_chatMessage;
	}

	void Deserialize(ServerSerializer& _serializer) override
	{
		ServerPacketBase::Deserialize(_serializer);

		_serializer >> m_userID;
		_serializer >> m_chatMessage;
	}

};
