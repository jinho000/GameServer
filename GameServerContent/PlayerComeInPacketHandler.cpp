#include "pch.h"
#include "PlayerComeInPacketHandler.h"
#include <GameServerNet/TCPSession.h>
#include "ContentCore.h"

void PlayerComeInPacketHandler::Start()
{
	// Ŭ���̾�Ʈ�� �÷��� ������ ���� �� �����ؾ��Ѵ�
	// ���� ������ �����ϸ� �ٸ� ������ �ִ� ������ �޾� ���� �� ���������� �Ѿ���Ե�


	// �ٸ� �÷��̾�� ���� ������ ���� �˸���
	// ���� ������ ������ �����ϰ� �������Ѵ�
	ServerSerializer sr;
	*m_packet >> sr;
	m_TCPSession->GetTCPListener()->BroadCast(sr.GetBuffer());
	
	
	// �������ִ� �ٸ� ������ ���� ���� ������
	
	// ������ ���Ӽ���(���߿��� �������� �ٲٱ�)
	//const std::unordered_map<uint64_t, std::shared_ptr<ClientPlayer>>& allPlayer = ContentCore::GetAllPlayer();
	//AllPlayerInfoPacket packet;
	//auto iter = allPlayer.begin();
	//while (iter != allPlayer.end())
	//{
	//	packet.AllPlayerInfo.push_back(iter->second->GetPlayerData());
	//	++iter;
	//}

	//ServerSerializer sr2;
	//packet >> sr2;
	//m_TCPSession->Send(sr2.GetBuffer());
	
}
