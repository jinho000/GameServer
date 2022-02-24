#pragma once
#include "ClientPacketBase.h"
#include "CoreMinimal.h"

// 채팅 패킷
// 패킷 구성: [패킷타입] [m_userID] [m_ChatMessage]
class ChatMessagePacket : public ClientPacketBase
{
public: // member var
	std::string m_userID;
	std::string m_chatMessage;

public: // default
	ChatMessagePacket()
	: ClientPacketBase(PacketType::CHAT_MESSAGE)
	{
	}

	ChatMessagePacket(const FString& _userID, const FString& _ChatMessage)
		: ClientPacketBase(PacketType::CHAT_MESSAGE)
		, m_userID(FTCHARToUTF8(*_userID).Get())
		, m_chatMessage(FTCHARToUTF8(*_ChatMessage).Get())
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

	virtual void Serialize(ClientSerializer& _serializer) override
	{
		//ClientPacketBase::Serialize(_serializer);
		_serializer << m_userID;
		_serializer << m_chatMessage;
	}

	virtual void Deserialize(ClientSerializer& _serializer) override
	{
		ClientPacketBase::Deserialize(_serializer);
		_serializer >> m_userID;
		_serializer >> m_chatMessage;
	}


};