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

	// ������ Ȯ��

	// ID�� �������� ��������
	UserTable_SelectIDToUserInfo SelectQuery(m_packet->ID);
	std::string userID = m_packet->ID;
	SelectQuery.DoQuery();
	std::shared_ptr<UserRow> data = SelectQuery.RowData;

	// ��ü ������ ��������
	UserTable_AllUserInfo queryAllUserInfo;
	queryAllUserInfo.DoQuery();
	std::vector<std::shared_ptr<UserRow>> datas = queryAllUserInfo.RowDatas;


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
