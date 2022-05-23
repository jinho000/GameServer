#include "pch.h"
#include "PlayerUpdatePacketHandler.h"
#include "ContentCore.h"

void PlayerUpdatePacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

// UDP에서 사용
void PlayerUpdatePacketHandler::Start()
{
	// 들어온 플레이어 데이터를 서버에 저장
	ContentCore::SetPlayerData(m_packet->PlayerData);

	// 서버에 접속한 다른 플레이어들에게 패킷 전달

}
