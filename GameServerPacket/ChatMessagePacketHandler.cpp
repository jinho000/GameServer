#include "pch.h"
#include "ChatMessagePacketHandler.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerString.h"
#include "GameServerNet/TCPSession.h"
#include "GameServerNet/TCPListener.h"

ChatMessagePacketHandler::ChatMessagePacketHandler(PtrSTCPSession _TCPSession, PtrSChatMsgPacket _packet)
	: m_TCPSession(_TCPSession)
	, m_packet(_packet)
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

	// ä�ø޼�����Ŷ�� UTF8�� �޾� �״�� ����
	ServerSerializer sr;
	(*m_packet) >> sr;

	// ����� ��� ���ǿ� ��Ŷ����
	 m_TCPSession->GetParent<TCPListener>()->BroadCast(sr.GetBuffer());
}

