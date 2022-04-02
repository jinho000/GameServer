#include "pch.h"
#include "JoinPacketHandler.h"

#include <GameServerBase/ServerString.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/DBQueue.h>

#include "UserTable.h"

JoinPacketHandler::JoinPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<JoinPacket> _packet)
	: PacketHandlerBase(_TCPSession, _packet)
{
}

JoinPacketHandler::~JoinPacketHandler()
{
}

void JoinPacketHandler::DBThreadRequestJoin()
{
	JoginResultPacket resultPacket;
	ServerSerializer sr;

	UserTable_SelectIDToUserInfo selectQuery(m_packet->ID);
	if (true == selectQuery.DoQuery())
	{
		ServerDebug::LogInfo("ID is already exist");

		// ������� ���̵� �̹� ����
		resultPacket.JoginResultCode = EResultCode::ID_ERROR;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());
		return;
	}

	UserTable_InsertUserInfo query(m_packet->ID, m_packet->PW);
	if (false == query.DoQuery())
	{
		// ���Խ���
		ServerDebug::AssertDebugMsg("Insert Query error");
		return;
	}

	ServerDebug::LogInfo("Insert OK");

	// ���Լ���
	resultPacket.JoginResultCode = EResultCode::OK;
	resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());
}

void JoinPacketHandler::Start()
{
	ServerDebug::LogInfo("Join Request Packet");

	std::string ID; ServerString::UTF8ToANSI(m_packet->ID, ID);
	std::string PW; ServerString::UTF8ToANSI(m_packet->PW, PW);

	ServerDebug::LogInfo("ID: " + ID);
	ServerDebug::LogInfo("PW: " + PW);

	DBQueue::EnQueue(std::bind(&JoinPacketHandler::DBThreadRequestJoin, std::dynamic_pointer_cast<JoinPacketHandler>(shared_from_this())));
}
