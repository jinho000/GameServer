#pragma once
#include "PacketHandlerBase.h"

// �α��� ��� ��Ŷ�� ó���ϱ� ���� �ڵ鷯
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

