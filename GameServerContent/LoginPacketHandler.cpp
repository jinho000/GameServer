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
#include <GameServerCore/ServerCore.h>

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
		m_loginResultPacket.LoginResultCode = ELoginResultCode::ID_ERROR;
		NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendLoginResult, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
		return;
	}


	std::shared_ptr<UserRow> userData = SelectQuery.RowData;
	if (m_packet->PW != userData->Pw)
	{
		ServerDebug::LogInfo("Mismatch of passwords");

		// 비밀번호가 일치하지 않음
		m_loginResultPacket.LoginResultCode = ELoginResultCode::PW_ERROR;
		NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendLoginResult, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
		return;
	}
	
	
	// 유저 데이터 저장
	// 로그인 완료 후 유저의 정보를 세션에 저장
	std::shared_ptr<SessionUserDBData> sessionUserDBData = std::make_shared<SessionUserDBData>();
	sessionUserDBData->UserInfo = userData;
	m_TCPSession->SetLink(EDBTable::USER, sessionUserDBData);

	m_userData = userData;

	
	// 로그인 완료
	ServerDebug::LogInfo("Login OK");
	m_loginResultPacket.LoginResultCode = ELoginResultCode::OK;

	// 로그인시 UDP포트도 같이 보내기
	m_loginResultPacket.UDPPort = ServerCore::GetUDPSession(0)->GetEndPoint().GetPort();

	NetQueue::EnQueue(std::bind(&LoginPacketHandler::NetThreadSendLoginResult, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));

}

void LoginPacketHandler::NetThreadSendLoginResult()
{
	// 확인 패킷 전달
	ServerSerializer sr;
	m_loginResultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());


	// 로그인이 완료된 경우에만 디비에서 캐릭터 정보 가져오기
	if (ELoginResultCode::OK == m_loginResultPacket.LoginResultCode)
	{
		// 유저의 캐릭터 정보 가져오기
		DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckCharList, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
	}
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
	ServerDebug::LogInfo("Character List Count : " + std::to_string(SelectQuery.RowDatas.size()));


	// 패킷에 데이터 채워넣기
	m_CharacterListPacket.CharacterList.resize(SelectQuery.RowDatas.size());
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

	// 세션이 가지고있는 유저 정보에 유저의 캐릭터 리스트 저장
	std::shared_ptr<SessionUserDBData> sessionUserDBData = m_TCPSession->GetLink<SessionUserDBData>(EDBTable::USER);
	sessionUserDBData->UserCharacterList = m_CharacterListPacket.CharacterList;
	
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

	m_loginResultPacket.LoginResultCode = ELoginResultCode::FAIL;
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckLogin, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}
