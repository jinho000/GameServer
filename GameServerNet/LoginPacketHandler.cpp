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
	// DB�� ���� ������ ó�� ��û
	// 1 ���� ������ DBĿ���͸� ����� ó��
	//   -> ?
	//
	// 2 DB�Ŵ������� DB�� ����� Ŀ���͸� ������ �����, �����尡 Ŀ���͸� ��û �� ó��
	//   -> � �����尡 ��û�ߴ��� �˱� �����
	// 
	// 3 Thread local�� �����帶�� Ŀ���͸� ���÷� ����� �ΰ� ���� ���
	//   
}

void LoginPacketHandler::ResultSend()
{
}

void LoginPacketHandler::Start()
{
	ServerDebug::LogInfo("ID: " + m_packet->ID);
	ServerDebug::LogInfo("PW: " + m_packet->PW);

	// DB�� ó�� ��û
	// ���Լ��ȿ��� ��� ó���Ϸ��� DB���� �� ����� �Ë����� ��ٷ����� 
	// DB���� ����� ���� ó���ϵ��� JobQueue�� ���� ó��(DBQueue)
	// 

	// ������� �� �ݹ��Լ�
	{
		// ��� ���� �� Ȯ�� ��Ŷ ����
		LoginResultPacket resultPacket;
		resultPacket.LoginResultCode = EResultCode::OK;

		ServerSerializer sr;
		resultPacket >> sr;

		m_TCPSession->Send(sr.GetBuffer());
	}
}
