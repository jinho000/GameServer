#include "pch.h"
#include "PlayerUpdatePacketHandler.h"

void PlayerUpdatePacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
}

// UDP���� ���
void PlayerUpdatePacketHandler::Start()
{
	int a = 0;
}
