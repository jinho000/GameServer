#pragma once
#include "ServerToClient.h"
#include "ClientToServer.h"
#include "ServerAndClient.h"

class ChatMessagePacketHandler
{
private: // member var
	PtrSTCPSession		m_TCPSession;
	PtrSChatMsgPacket	m_packet;

public: // default
	ChatMessagePacketHandler() = delete;
	ChatMessagePacketHandler(PtrSTCPSession _TCPSession, PtrSChatMsgPacket _packet);
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

