#include "pch.h"
#include "ContentCore.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/ServerSectionManager.h>
#include <GameServerCore/ServerSection.h>

#include "PacketDispatcher.h"
#include "ContentEnum.h"

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

PacketDispatcher<TCPSession> dispatcher;

void ContentCore::RecvEvent(std::shared_ptr<TCPSession> _tcpSession, const std::vector<unsigned char>& _recvBuffer)
{
	dispatcher.Dispatch(_recvBuffer, _tcpSession);
}

void ContentCore::CloseEvent(std::shared_ptr<TCPSession> _tcpSession)
{
	std::string LogText = std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
	ServerDebug::LogInfo(LogText + " Socket Disconnected");
}

void ContentCore::UDPRecvEvent(std::shared_ptr<UDPSession> _udpSession, const std::vector<unsigned char>& _recvBuffer, IPEndPoint& _clientEndPoint)
{
	int a = 0;
}

void ContentCore::UserStart()
{
	// TCP Accept 捞亥飘 贸府
	SetAcceptCallBack(ContentCore::AcceptEvent);

	// UDP Session 积己
	CreateUDPSession(4);

	SetUDPRecvCallBack(ContentCore::UDPRecvEvent);


	// 冀记贸府
	//ServerSectionManager::GetInst()->Init(3);
	//ServerSectionManager::GetInst()->CreateSection<TestSection>(0, ESectionType::NONE);


	
}
