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

	// ä�ø޼�����Ŷ�� UTF8�� �޾� �״�� ����
	ServerSerializer sr;
	(*m_packet) >> sr;

	// ����� ��� ���ǿ� ��Ŷ����
	 m_TCPSession->GetParent<TCPListener>()->BroadCast(sr.GetBuffer());
}

