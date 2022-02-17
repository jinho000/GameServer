#pragma once
#include "ServerPacketBase.h"

// 용도 :
// 분류 :
// 첨언 :
class ChatMessagePacket : public ServerPacketBase
{
private: // member var
	std::string m_userID;
	std::string m_chatMessage;

public: // default
	ChatMessagePacket();
	~ChatMessagePacket();

	ChatMessagePacket(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket(ChatMessagePacket&& _other) = delete;

protected:
	ChatMessagePacket& operator=(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket& operator=(const ChatMessagePacket&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ServerSerializer& _serializer) override;
	virtual void Deserialize(ServerSerializer& _serializer) override;

	const std::string& GetUserID() { return m_userID; }
	const std::string& GetChatMessage() { return m_chatMessage; }
};

