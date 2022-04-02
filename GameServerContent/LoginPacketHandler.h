#pragma once
#include "PacketHandlerBase.h"

// �α��� ��Ŷó�� �Լ� Ŭ����
// �α��� ���� ó���� �Լ��� �ϳ��� Ŭ������ ��� ����
class LoginPacketHandler : public PacketHandlerBase<LoginPacket>
{
public: // default
	LoginPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<LoginPacket> _packet);
	~LoginPacketHandler();

	LoginPacketHandler(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler(LoginPacketHandler&& _other) = delete;
	LoginPacketHandler& operator=(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler& operator=(const LoginPacketHandler&& _other) = delete;

private:
	void DBThreadCheckDB(); // dbó��

public: // member Func
	void Start();

};

