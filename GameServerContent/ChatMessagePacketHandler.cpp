#include "pch.h"
#include "ChatMessagePacketHandler.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerString.h"
#include "GameServerNet/TCPSession.h"
#include "GameServerNet/TCPListener.h"

ChatMessagePacketHandler::ChatMessagePacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<ChatMessagePacket> _packet)
	: PacketHandlerBase(_TCPSession, _packet)
{
}

ChatMessagePacketHandler::~ChatMessagePacketHandler()
{
}

void ChatMessagePacketHandler::Start()
{
	std::string userID;
	std::string message;
	ServerString::UTF8ToANSI(m_packet->ID, userID);
	ServerString::UTF8ToANSI(m_packet->Message, message);

	ServerDebug::LogInfo("User ID: " + userID);
	ServerDebug::LogInfo("Message: " + message);

	// 채팅메세지패킷은 UTF8로 받아 그대로 전달
	ServerSerializer sr;
	(*m_packet) >> sr;

	// 연결된 모든 세션에 패킷전달
	 m_TCPSession->GetParent<TCPListener>()->BroadCast(sr.GetBuffer());
}

