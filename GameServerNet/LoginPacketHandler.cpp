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
	// DB에 접근 데이터 처리 요청
	// 1 로컬 변수로 DB커넥터를 만들어 처리
	//   -> ?
	//
	// 2 DB매니저에서 DB에 연결된 커넥터를 여러개 만들고, 스레드가 커넥터를 요청 후 처리
	//   -> 어떤 스레드가 요청했는지 알기 어려움
	// 
	// 3 Thread local로 스레드마다 커넥터를 로컬로 만들어 두고 꺼내 사용
	//   
}

void LoginPacketHandler::ResultSend()
{
}

void LoginPacketHandler::Start()
{
	ServerDebug::LogInfo("ID: " + m_packet->ID);
	ServerDebug::LogInfo("PW: " + m_packet->PW);

	// DB에 처리 요청
	// 이함수안에서 모두 처리하려면 DB접근 후 결과가 올떄까지 기다려야함 
	// DB에서 결과가 오면 처리하도록 JobQueue를 만들어서 처리(DBQueue)
	// 

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
