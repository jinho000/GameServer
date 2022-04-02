#include "pch.h"
#include "LoginPacketHandler.h"
#include "ServerSerializer.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerThread.h"
#include "GameServerBase/ServerString.h"
#include "GameServerNet/DBConnecter.h"
#include "GameServerNet/TCPSession.h"

#include <GameServerCore/DBQueue.h>

#include "UserTable.h"

LoginPacketHandler::LoginPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<LoginPacket> _packet)
	: PacketHandlerBase(_TCPSession, _packet)
{

}

LoginPacketHandler::~LoginPacketHandler()
{
}

void LoginPacketHandler::DBThreadCheckDB()
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

	LoginResultPacket resultPacket;
	ServerSerializer sr;

	// 데이터 확인
	// ID로 유저정보 가져오기
	UserTable_SelectIDToUserInfo SelectQuery(m_packet->ID);

	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::LogInfo("ID is not exist");

		// 유저 아이디가 없음
		resultPacket.LoginResultCode = EResultCode::ID_ERROR;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());
		return;
	}
	
	
	std::shared_ptr<UserRow> userData = SelectQuery.RowData;
	if (m_packet->PW != userData->Pw)
	{
		ServerDebug::LogInfo("Mismatch of passwords");

		// 비밀번호가 일치하지 않음
		resultPacket.LoginResultCode = EResultCode::PW_ERROR;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());

		return;
	}
	
	ServerDebug::LogInfo("Login OK");

	// 결과 검증 후 확인 패킷 전달
	resultPacket.LoginResultCode = EResultCode::OK;
	resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());
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
	DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckDB, std::dynamic_pointer_cast<LoginPacketHandler>(shared_from_this())));
}
