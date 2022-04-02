#pragma once
#include "PacketHandlerBase.h"

class ChatMessagePacketHandler : public PacketHandlerBase<ChatMessagePacket>
{
public: // default
	ChatMessagePacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<ChatMessagePacket> _packet);
	~ChatMessagePacketHandler();

	ChatMessagePacketHandler(const ChatMessagePacketHandler& _other) = delete;
	ChatMessagePacketHandler(ChatMessagePacketHandler&& _other) = delete;
	ChatMessagePacketHandler& operator=(const ChatMessagePacketHandler& _other) = delete;
	ChatMessagePacketHandler& operator=(const ChatMessagePacketHandler&& _other) = delete;

private:

public: // member Func
	void Start();
};

