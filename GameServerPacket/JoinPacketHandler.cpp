#include "pch.h"
#include "JoinPacketHandler.h"
#include "DBQueue.h"
#include "UserTable.h"

JoinPacketHandler::JoinPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<JoinPacket> _packet)
	: m_TCPSession(_TCPSession)
	, m_packet(_packet)
{
}

JoinPacketHandler::~JoinPacketHandler()
{
}

void JoinPacketHandler::DBThreadRequestJoin()
{
	UserTable_InsertUserInfo query(m_packet->ID, m_packet->PW);
	query.DoQuery();


}

void JoinPacketHandler::Start()
{
	DBQueue::EnQueue(std::bind(&JoinPacketHandler::DBThreadRequestJoin, shared_from_this()));
}
