#pragma once
#include "ChatMessagePacket.h"


class ChatPacketHandler
{
private: // member var
	PtrSTCPSession		m_TCPSession;
	PtrSChatMsgPacket	m_packet;

public: // default
	ChatPacketHandler() = delete;
	ChatPacketHandler(PtrSTCPSession _TCPSession, PtrSChatMsgPacket _packet);
	~ChatPacketHandler();

	ChatPacketHandler(const ChatPacketHandler& _other) = delete;
	ChatPacketHandler(ChatPacketHandler&& _other) = delete;

protected:
	ChatPacketHandler& operator=(const ChatPacketHandler& _other) = delete;
	ChatPacketHandler& operator=(const ChatPacketHandler&& _other) = delete;

private:

public: // member Func
	void Start();
};

