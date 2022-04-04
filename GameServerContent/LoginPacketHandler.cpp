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
	// DB에 접근 데이터 처리 요청
	// 1 로컬 변수로 DB커넥터를 만들어 처리
	//   -> 함수가 실행될때마다 디비에 계속 연결을 해줘야하므로 비효울적
	//
	// 2 DB매니저에서 DB에 연결된 커넥터를 여러개 만들고, 스레드가 커넥터를 요청 후 처리
	//   -> 어떤 스레드가 요청했는지 알기 어려움
	// 
	// 3 Thread local로 스레드마다 디비커넥터를 스레드의 로컬메모리로 만들어 두고 꺼내 사용
	//   -> ServerThread::GetLocalData<DBConnecter>();
	//   
	// 쿼리문 클래스에서 스레드 로컬의 디비커넥터객체를 가져와 사용한다
	// DBConnecter* pDBConnecter = ServerThread::GetLocalData<DBConnecter>();

	ServerSerializer sr;

	// 데이터 확인
	// ID로 유저정보 가져오기
	UserTable_SelectIDToUserInfo SelectQuery(m_packet->ID);

	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::LogInfo("ID is not exist");

		// 유저 아이디가 없음
		m_loginResultPacket.LoginResultCode = EResultCode::ID_ERROR;
		m_loginResultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());
		return;
	}


	std::shared_ptr<UserRow> userData = SelectQuery.RowData;
	if (m_packet->PW != userData->Pw)
	{
		ServerDebug::LogInfo("Mismatch of passwords");

		// 비밀번호가 일치하지 않음
		m_loginResultPacket.LoginResultCode = EResultCode::PW_ERROR;
		m_loginResultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());

		return;
	}
	
	// 유저 데이터 저장
	m_userData = userData;

	// NetQueue를 통해 결과값 전달
	NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendLoginResult, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}

void LoginPacketHandler::NetThreadSendLoginResult()
{
	ServerDebug::LogInfo("Login OK");

	// 확인 패킷 전달
	ServerSerializer sr;
	m_loginResultPacket.LoginResultCode = EResultCode::OK;
	m_loginResultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());


	// 유저의 캐릭터 정보를 받기위해 세션에 정보 저장
	// 세션에 유저 정보를 미리 받아놓는다
	// (유저정보가 필요할때 디비에 갔다올필요가 없다)
	// (서버의 정보와 디비의 정보를 계속 동기화시켜줘야한다)
	ServerDebug::LogInfo("Save user info to session");
	ServerDebug::LogInfo(std::string("user Index : ") + std::to_string(m_userData->Index));

	std::shared_ptr<SessionUserDBData> sessionUserDB = std::make_shared<SessionUserDBData>();
	sessionUserDB->UserInfo = m_userData;
	m_TCPSession->SetLink(EDBTable::USER, sessionUserDB);


	// 유저의 캐릭터 정보 가져오기
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

	// 패킷에 데이터 채워넣기
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

	// 캐릭터정보를 넷스레드를 통해 전달
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

	// DB에 처리 요청
	// DB에 관한일은 DB큐에서 처리한다
	// 
	// 핸들러에서 이함수를 실행 후 종료되면, 핸들러 객체가 사라지기때문에 shared_from_this 사용

	m_loginResultPacket.LoginResultCode = EResultCode::FAIL;
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckLogin, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}
