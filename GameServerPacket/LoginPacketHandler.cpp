#include "pch.h"
#include "LoginPacketHandler.h"
#include "ServerSerializer.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerThread.h"
#include "GameServerNet/DBConnecter.h"
#include "GameServerNet/TCPSession.h"

#include <GameServerPacket/DBQueue.h>

#include "UserTable.h"

LoginPacketHandler::LoginPacketHandler(PtrSTCPSession _TCPSession, PtrSLoginPacket _packet)
	: m_TCPSession(_TCPSession)
	, m_packet(_packet)
{

}

LoginPacketHandler::~LoginPacketHandler()
{
}

void LoginPacketHandler::DBThreadCheckDB()
{
	// 
	// DB�� ���� ������ ó�� ��û
	// 1 ���� ������ DBĿ���͸� ����� ó��
	//   -> �Լ��� ����ɶ����� ��� ��� ������ ������ϹǷ� ��ȿ����
	//
	// 2 DB�Ŵ������� DB�� ����� Ŀ���͸� ������ �����, �����尡 Ŀ���͸� ��û �� ó��
	//   -> � �����尡 ��û�ߴ��� �˱� �����
	// 
	// 3 Thread local�� �����帶�� ���Ŀ���͸� �������� ���ø޸𸮷� ����� �ΰ� ���� ���
	//   -> ServerThread::GetLocalData<DBConnecter>();
	//   
	//DBConnecter* pDBConnecter = ServerThread::GetLocalData<DBConnecter>();

	LoginResultPacket resultPacket;
	ServerSerializer sr;

	// ������ Ȯ��
	// ID�� �������� ��������
	UserTable_SelectIDToUserInfo SelectQuery(m_packet->ID);

	if (false == SelectQuery.DoQuery())
	{
		// ���� ���̵� ����
		resultPacket.LoginResultCode = EResultCode::ID_ERROR;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());

		return;
	}
	
	
	std::shared_ptr<UserRow> userData = SelectQuery.RowData;
	if (m_packet->PW != userData->Pw)
	{
		// ��й�ȣ�� ��ġ���� ����
		resultPacket.LoginResultCode = EResultCode::PW_ERROR;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());

		return;
	}
	

	// ��� ���� �� Ȯ�� ��Ŷ ����
	resultPacket.LoginResultCode = EResultCode::OK;
	resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());
}

void LoginPacketHandler::ResultSend()
{
}

void LoginPacketHandler::Start()
{
	//ServerDebug::LogInfo("ID: " + m_packet->ID);
	//ServerDebug::LogInfo("PW: " + m_packet->PW);

	// DB�� ó�� ��û
	// ���Լ��ȿ��� ��� ó���Ϸ��� DB���� �� ����� �Ë����� ��ٷ����� 
	// DB���� ����� ���� ó���ϵ��� JobQueue�� ���� ó��(DBQueue)
	// 
	// �ڵ鷯���� ���Լ��� ���� �� ����Ǹ�, �ڵ鷯 ��ü�� ������⶧���� shared_from_this ���
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckDB, shared_from_this()));
}
