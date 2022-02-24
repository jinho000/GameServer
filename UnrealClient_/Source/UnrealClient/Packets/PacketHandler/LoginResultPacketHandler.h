#pragma once
#include "PacketHandlerBase.h"

// �α��� ��� ��Ŷ�� ó���ϱ� ���� �ڵ鷯
class LoginResultPacketHandler : public PacketHandlerBase
{
private: // member var
	std::shared_ptr<LoginResultPacket> m_packet;

public: // default
	LoginResultPacketHandler() = delete;
	LoginResultPacketHandler(const std::shared_ptr<LoginResultPacket>& _packet);
	~LoginResultPacketHandler();

	LoginResultPacketHandler(const LoginResultPacketHandler& _other) = delete;
	LoginResultPacketHandler(LoginResultPacketHandler&& _other) = delete;

protected:
	LoginResultPacketHandler& operator=(const LoginResultPacketHandler& _other) = delete;
	LoginResultPacketHandler& operator=(const LoginResultPacketHandler&& _other) = delete;

private:

public: // member Func
	void Start();
};

