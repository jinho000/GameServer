#include "pch.h"
#include "JoinPacketHandler.h"

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

	// ���Լ���
	resultPacket.JoginResultCode = EResultCode::OK;
	resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());
}

void JoinPacketHandler::Start()
{
	DBQueue::EnQueue(std::bind(&JoinPacketHandler::DBThreadRequestJoin, std::dynamic_pointer_cast<JoinPacketHandler>(shared_from_this())));
}
