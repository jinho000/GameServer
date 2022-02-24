#pragma once
#include "PacketHandlerBase.h"

// 로그인 결과 패킷을 처리하기 위한 핸들러
class ChatMessagePacketHandler : public PacketHandlerBase
{
private: // member var
	std::shared_ptr<ChatMessagePacket> m_packet;

public: // default
	ChatMessagePacketHandler() = delete;
	ChatMessagePacketHandler(const std::shared_ptr<ChatMessagePacket>& _packet);
	~ChatMessagePacketHandler();

	ChatMessagePacketHandler(const ChatMessagePacketHandler& _other) = delete;
	ChatMessagePacketHandler(ChatMessagePacketHandler&& _other) = delete;

protected:
	ChatMessagePacketHandler& operator=(const ChatMessagePacketHandler& _other) = delete;
	ChatMessagePacketHandler& operator=(const ChatMessagePacketHandler&& _other) = delete;

private:

public: // member Func
	void Start();
};

