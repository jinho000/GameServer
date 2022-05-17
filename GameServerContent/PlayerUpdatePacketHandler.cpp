#include "pch.h"
#include "PlayerUpdatePacketHandler.h"
#include <GameServerCore/ServerCore.h>

void PlayerUpdatePacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

// UDP에서 사용
void PlayerUpdatePacketHandler::Start()
{
	// echo test
	
	const std::vector<IPEndPoint>& test =  ServerCore::GetAllUserEndPoint();

	for (const IPEndPoint& userEndPoint : test)
	{
		ServerSerializer sr;
		*m_packet >> sr;
		m_UDPSession->Send(sr.GetBuffer(), userEndPoint);
	}

}
