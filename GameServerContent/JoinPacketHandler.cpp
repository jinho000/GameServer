#include "pch.h"
#include "JoinPacketHandler.h"

#include <GameServerBase/ServerString.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/DBQueue.h>

#include "UserTable.h"

void JoinPacketHandler::DBThreadRequestJoin()
{
	JoginResultPacket resultPacket;
	ServerSerializer sr;

	UserTable_SelectIDToUserInfo selectQuery(m_packet->ID);
	if (true == selectQuery.DoQuery())
	{
		ServerDebug::LogInfo("ID is already exist");

		// 만드려는 아이디가 이미 있음
		resultPacket.JoginResultCode = EJoinResultCode::ID_DUPLE;
		resultPacket >> sr;
		m_TCPSession->Send(sr.GetBuffer());
		return;
	}

	UserTable_InsertUserInfo query(m_packet->ID, m_packet->PW);
	if (false == query.DoQuery())
	{
		// 삽입실패
		ServerDebug::AssertDebugMsg("Insert Query error");
		return;
	}

	ServerDebug::LogInfo("Insert OK");

	// 삽입성공
	resultPacket.JoginResultCode = EJoinResultCode::OK;
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
