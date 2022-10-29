#include "pch.h"
#include "ContentCore.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/ServerSectionManager.h>
#include <GameServerCore/ServerSection.h>
#include <GameServerNet/UDPSession.h>
#include "ContentEnum.h"
#include "ContentManager.h"
#include "ContentQueue.h"


PacketDispatcher<TCPSession>	ContentCore::TcpDispatcher;
UDPPacketDispatcher				ContentCore::UdpDispatcher;

void ContentCore::AcceptEvent(std::shared_ptr<TCPSession> _tcpSession)
{
	_tcpSession->SetCallBack(RecvEvent, CloseEvent);

	std::string log = std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
	log += " Socket Connected";
	ServerDebug::LogInfo(log);
}

void ContentCore::RecvEvent(std::shared_ptr<TCPSession> _tcpSession, const std::vector<unsigned char>& _recvBuffer)
{
	// Dispatcher������ �����޸𸮿� ���� ��찡 �����Ƿ� ����ȭ���� �ʾƵ� �ȴ�
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
	// TCP Accept �̺�Ʈ ó��
	SetAcceptCallBack(ContentCore::AcceptEvent);

	// UDP Session ����
	CreateUDPSession(4);
	SetUDPRecvCallBack(ContentCore::UDPRecvEvent);

	// SessionQueue �����
	ContentQueue::Init();

	// ContentManager ó��
	// ������ ������ ���� ������ ó��
	ContentManager::Init();
}

void ContentCore::UserEnd()
{
	ContentManager::Destroy();
	ContentQueue::Destroy();
}
