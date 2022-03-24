#include "pch.h"
#include "LoginPacketHandler.h"
#include "ServerSerializer.h"
#include "TCPSession.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerThread.h"
#include "GameServerNet/DBConnecter.h"
#include "DBQueue.h"

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

	DBConnecter* pDBConnecter = ServerThread::GetLocalData<DBConnecter>();

	int a = 0;
}

void LoginPacketHandler::ResultSend()
{
}

void LoginPacketHandler::Start()
{
	//ServerDebug::LogInfo("ID: " + m_packet->ID);
	//ServerDebug::LogInfo("PW: " + m_packet->PW);

	// DB에 처리 요청
	// 이함수안에서 모두 처리하려면 DB접근 후 결과가 올떄까지 기다려야함 
	// DB에서 결과가 오면 처리하도록 JobQueue를 만들어서 처리(DBQueue)
	// 
	// 핸들러에서 이함수를 실행 후 종료되면, 핸들러 객체가 사라지기때문에 shared_from_this 사용
	//DBQueue::EnQueue(std::bind(&LoginPacketHandler::DBThreadCheckDB, shared_from_this()));


	// 결과검증 후 콜백함수
	{
		// 결과 검증 후 확인 패킷 전달
		LoginResultPacket resultPacket;
		resultPacket.LoginResultCode = EResultCode::OK;

		ServerSerializer sr;
		resultPacket >> sr;

		m_TCPSession->Send(sr.GetBuffer());
	}
}
