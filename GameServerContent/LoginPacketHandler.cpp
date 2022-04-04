#include "pch.h"
#include "LoginPacketHandler.h"
#include "ServerSerializer.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerThread.h"
#include "GameServerBase/ServerString.h"
#include "GameServerNet/DBConnecter.h"
#include "GameServerNet/TCPSession.h"

#include <GameServerCore/DBQueue.h>
#include <GameServerCore/NetQueue.h>

#include "UserTable.h"
#include "CharacterTable.h"
#include "SessionUserDBData.h"
#include "DBTableEHeader.h"

void LoginPacketHandler::DBThreadCheckLogin()
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
	// ������ Ŭ�������� ������ ������ ���Ŀ���Ͱ�ü�� ������ ����Ѵ�
	// DBConnecter* pDBConnecter = ServerThread::GetLocalData<DBConnecter>();

	ServerSerializer sr;

	// ������ Ȯ��
	// ID�� �������� ��������
	UserTable_SelectIDToUserInfo SelectQuery(m_packet->ID);

	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::LogInfo("ID is not exist");

		// ���� ���̵� ����
		m_loginResultPacket.LoginResultCode = EResultCode::ID_ERROR;
		m_loginResultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());
		return;
	}


	std::shared_ptr<UserRow> userData = SelectQuery.RowData;
	if (m_packet->PW != userData->Pw)
	{
		ServerDebug::LogInfo("Mismatch of passwords");

		// ��й�ȣ�� ��ġ���� ����
		m_loginResultPacket.LoginResultCode = EResultCode::PW_ERROR;
		m_loginResultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());

		return;
	}
	
	// ���� ������ ����
	m_userData = userData;

	// NetQueue�� ���� ����� ����
	NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendLoginResult, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}

void LoginPacketHandler::NetThreadSendLoginResult()
{
	ServerDebug::LogInfo("Login OK");

	// Ȯ�� ��Ŷ ����
	ServerSerializer sr;
	m_loginResultPacket.LoginResultCode = EResultCode::OK;
	m_loginResultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());


	// ������ ĳ���� ������ �ޱ����� ���ǿ� ���� ����
	// ���ǿ� ���� ������ �̸� �޾Ƴ��´�
	// (���������� �ʿ��Ҷ� ��� ���ٿ��ʿ䰡 ����)
	// (������ ������ ����� ������ ��� ����ȭ��������Ѵ�)
	ServerDebug::LogInfo("Save user info to session");
	ServerDebug::LogInfo(std::string("user Index : ") + std::to_string(m_userData->Index));

	std::shared_ptr<SessionUserDBData> sessionUserDB = std::make_shared<SessionUserDBData>();
	sessionUserDB->UserInfo = m_userData;
	m_TCPSession->SetLink(EDBTable::USER, sessionUserDB);


	// ������ ĳ���� ���� ��������
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckCharList, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}

void LoginPacketHandler::DBThreadCheckCharList()
{
	ServerDebug::LogInfo("Get User Character List");
	CharacterTable_SelectUserCharacters SelectQuery(m_userData->Index);
	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::AssertDebugMsg("Fail Select Query");
		return;
	}

	// ��Ŷ�� ������ ä���ֱ�
	m_CharacterListPacket.CharacterList.resize(SelectQuery.RowDatas.size());
	ServerDebug::LogInfo("Character List Count : " + std::to_string(SelectQuery.RowDatas.size()));
	for (size_t i = 0; i < SelectQuery.RowDatas.size(); i++)
	{
		m_CharacterListPacket.CharacterList[i].Index = SelectQuery.RowDatas[i]->Index;
		m_CharacterListPacket.CharacterList[i].NickName = SelectQuery.RowDatas[i]->NickName;
		m_CharacterListPacket.CharacterList[i].UserIndex = SelectQuery.RowDatas[i]->UserIndex;
		m_CharacterListPacket.CharacterList[i].Att = SelectQuery.RowDatas[i]->Att;
		m_CharacterListPacket.CharacterList[i].Hp = SelectQuery.RowDatas[i]->Hp;
		m_CharacterListPacket.CharacterList[i].LastRoomID = SelectQuery.RowDatas[i]->LastRoomID;
		m_CharacterListPacket.CharacterList[i].RoomX = SelectQuery.RowDatas[i]->RoomX;
		m_CharacterListPacket.CharacterList[i].RoomY = SelectQuery.RowDatas[i]->RoomY;
		m_CharacterListPacket.CharacterList[i].RoomZ = SelectQuery.RowDatas[i]->RoomZ;
	}

	// ĳ���������� �ݽ����带 ���� ����
	NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendCharList, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}

void LoginPacketHandler::NetThreadSendCharList()
{
	ServerSerializer sr;
	m_CharacterListPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());

	ServerDebug::LogInfo("Send Character List");
}


void LoginPacketHandler::Start()
{
	ServerDebug::LogInfo("Login Request Packet");

	std::string ID; ServerString::UTF8ToANSI(m_packet->ID, ID);
	std::string PW; ServerString::UTF8ToANSI(m_packet->PW, PW);

	ServerDebug::LogInfo("ID: " + ID);
	ServerDebug::LogInfo("PW: " + PW);

	// DB�� ó�� ��û
	// DB�� �������� DBť���� ó���Ѵ�
	// 
	// �ڵ鷯���� ���Լ��� ���� �� ����Ǹ�, �ڵ鷯 ��ü�� ������⶧���� shared_from_this ���

	m_loginResultPacket.LoginResultCode = EResultCode::FAIL;
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckLogin, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}
