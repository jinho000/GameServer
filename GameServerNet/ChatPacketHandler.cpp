#include "pch.h"
#include "ChatPacketHandler.h"
#include "GameServerBase/ServerDebug.h"
#include "TCPSession.h"
#include "TCPListener.h"

ChatPacketHandler::ChatPacketHandler(PtrSTCPSession _TCPSession, PtrSChatMsgPacket _packet)
	: m_TCPSession(_TCPSession)
	, m_packet(_packet)
{
}

ChatPacketHandler::~ChatPacketHandler()
{
}

void ChatPacketHandler::Start()
{
	std::string userID;
	std::string message;
	ServerString::UTF8ToANSI(m_packet->GetUserID(), userID);
	ServerString::UTF8ToANSI(m_packet->GetChatMessage(), message);

	ServerDebug::LogInfo("User ID: " + userID);
	ServerDebug::LogInfo("Message: " + message);

	// 채팅메세지패킷은 UTF8로 받아 그대로 전달
	ServerSerializer sr;
	(*m_packet) >> sr;

	// 연결된 모든 세션에 패킷전달
	 m_TCPSession->GetParent<TCPListener>()->BroadCast(sr.GetBuffer());
}

