#include "pch.h"
#include "ContentCore.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerPacket/PacketConvertor.h>
#include <GameServerPacket/PacketDispatcher.h>

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

	// FindSection("·Îºñ");
}

PacketDispatcher<TCPSession> dispatcher;

void ContentCore::RecvEvent(std::shared_ptr<TCPSession> _tcpSession, const std::vector<unsigned char>& _recBuffer)
{
	PacketConvertor convertor(_recBuffer);
	const PacketHandler<TCPSession>& handler = dispatcher.GetHandler(convertor.GetPacketType());
	handler(_tcpSession, convertor.GetPacket());
}

void ContentCore::CloseEvent(std::shared_ptr<TCPSession> _tcpSession)
{
	std::string LogText = std::to_string(static_cast<int>(_tcpSession->GetSessionSocket()));
	ServerDebug::LogInfo(LogText + " Socket Disconnected");
}

void ContentCore::UserStart()
{
	SetAcceptCallBack(ContentCore::AcceptEvent);
}
