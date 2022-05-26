#include "pch.h"
#include "PlayerUpdatePacketHandler.h"
#include "ContentManager.h"

void PlayerUpdatePacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

// UDP에서 사용
void PlayerUpdatePacketHandler::Start()
{
	ContentManager::GetInst()->BroadCastUDPPlayerData(m_packet->PlayerData, m_UDPSession);
}
