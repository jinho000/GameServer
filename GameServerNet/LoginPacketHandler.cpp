#include "pch.h"
#include "LoginPacketHandler.h"
#include "ServerSerializer.h"
#include "TCPSession.h"
#include "GameServerBase/ServerDebug.h"

LoginPacketHandler::LoginPacketHandler(PtrSTCPSession _TCPSession, PtrSLoginPacket _packet)
	: m_TCPSession(_TCPSession)
	, m_packet(_packet)
{

}

LoginPacketHandler::~LoginPacketHandler()
{
}

void LoginPacketHandler::DBCheck()
{
}

void LoginPacketHandler::ResultSend()
{
}

void LoginPacketHandler::Start()
{
	ServerDebug::LogInfo("ID: " + m_packet->ID);
	ServerDebug::LogInfo("PW: " + m_packet->PW);

	// ��� ���� �� Ȯ�� ��Ŷ ����
	LoginResultPacket resultPacket;
	resultPacket.LoginResultCode = EResultCode::OK;

	ServerSerializer sr;
	resultPacket >> sr;

	m_TCPSession->Send(sr.GetBuffer());
}
