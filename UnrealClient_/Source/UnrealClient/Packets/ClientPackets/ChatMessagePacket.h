#pragma once
#include "ClientPacketBase.h"
#include "CoreMinimal.h"

// 채팅 패킷
// 패킷 구성: [패킷타입] [m_userID] [m_ChatMessage]
class ChatMessagePacket : public ClientPacketBase
{
private: // member var
	std::string m_userID;
	std::string m_ChatMessage;

public: // default
	ChatMessagePacket();
	ChatMessagePacket(const FString& _userID, const FString& _ChatMessage);
	~ChatMessagePacket();

	ChatMessagePacket(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket(ChatMessagePacket&& _other) = delete;

protected:
	ChatMessagePacket& operator=(const ChatMessagePacket& _other) = delete;
	ChatMessagePacket& operator=(const ChatMessagePacket&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ClientSerializer& _serializer) override;
	virtual void Deserialize(ClientSerializer& _serializer) override;
};