#pragma once
#include "PacketHandlerBase.h"
#include "UserTable.h"

// �α��� ��Ŷó�� �Լ� Ŭ����
// �α��� ���� ó���� �Լ��� �ϳ��� Ŭ������ ��� ����
class LoginPacketHandler : public PacketHandlerBase<LoginPacket>
{
private:
	LoginResultPacket			m_loginResultPacket;
	CharacterListPacket			m_CharacterListPacket;
	std::shared_ptr<UserRow>	m_userData;

public: // default
	LoginPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<LoginPacket> _packet);
	~LoginPacketHandler();

	LoginPacketHandler(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler(LoginPacketHandler&& _other) = delete;
	LoginPacketHandler& operator=(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler& operator=(const LoginPacketHandler&& _other) = delete;

private:
	void DBThreadCheckLogin();  // �α��� ��� üũ
	void NetThreadSendLoginResult(); // �α��� ��� ����
	void DBThreadCheckCharList();
	void NetThreadSendCharList();

public: // member Func
	void Start();

};

