#include "pch.h"
#include "ContentCore.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/ServerSectionManager.h>
#include <GameServerCore/ServerSection.h>
#include "ContentEnum.h"

PacketDispatcher<TCPSession>	ContentCore::TcpDispatcher;
UDPPacketDispatcher				ContentCore::UdpDispatcher;

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::AcceptEvent(std::shared_ptr<TCPSession> _tcpSession)
{
	_tcpSession->SetCallBack(RecvEvent, CloseEvent);

	std::string log = std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
	log += " Socket Connected";
	ServerDebug::LogInfo(log);
}

void ContentCore::RecvEvent(std::shared_ptr<TCPSession> _tcpSession, const std::vector<unsigned char>& _recvBuffer)
{
	// Dispatcher에서는 공유메모리에 쓰는 경우가 없으므로 동기화하지 않아도 된다
	TcpDispatcher.Dispatch(_recvBuffer, _tcpSession);
}

void ContentCore::CloseEvent(std::shared_ptr<TCPSession> _tcpSession)
{
	std::string LogText = std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
	ServerDebug::LogInfo(LogText + " Socket Disconnected");
}

void ContentCore::UDPRecvEvent(std::shared_ptr<UDPSession> _udpSession, const std::vector<unsigned char>& _recvBuffer, IPEndPoint& _clientEndPoint)
{
	UdpDispatcher.Dispatch(_recvBuffer, _udpSession, _clientEndPoint);

}

void ContentCore::UserStart()
{
	// TCP Accept 이벤트 처리
	SetAcceptCallBack(ContentCore::AcceptEvent);

	// UDP Session 생성
	CreateUDPSession(4);
	SetUDPRecvCallBack(ContentCore::UDPRecvEvent);

	// 이동시 UDP로 패킷 받아오기 
	
	// 세션 만들기

}
