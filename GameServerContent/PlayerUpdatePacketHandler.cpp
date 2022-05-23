#include "pch.h"
#include "PlayerUpdatePacketHandler.h"
#include "ContentCore.h"

void PlayerUpdatePacketHandler::InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet, const IPEndPoint& _clientEndPoint)
{
	m_UDPSession = _UDPSession;
	m_packet = _packet;
	m_clientEndPoint = _clientEndPoint;
}

// UDP���� ���
void PlayerUpdatePacketHandler::Start()
{
	// ���� �÷��̾� �����͸� ������ ����
	ContentCore::SetPlayerData(m_packet->PlayerData);

	// ������ ������ �ٸ� �÷��̾�鿡�� ��Ŷ ����

}
