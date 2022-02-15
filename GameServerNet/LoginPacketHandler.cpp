#include "pch.h"
#include "LoginPacketHandler.h"
#include "LoginResultPacket.h"
#include "ServerSerializer.h"
#include "TCPSession.h"

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
	std::cout << "ID: " << m_packet->m_id << std::endl;;
	std::cout << "PW: " << m_packet->m_password << std::endl;;

	// ��� ���� �� Ȯ�� ��Ŷ ����
	LoginResultPacket resultPacket(EResultCode::OK);
	ServerSerializer sr;
	resultPacket >> sr;

	m_TCPSession->Send(sr.GetBuffer());
}
