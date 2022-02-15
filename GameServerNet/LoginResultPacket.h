#pragma once
#include "ServerPacketBase.h"

// �α��� ��� ���� ��Ŷ
class LoginResultPacket : public ServerPacketBase
{
private: // member var
	EResultCode m_resultCode;

public: // default
	LoginResultPacket() = delete;
	LoginResultPacket(EResultCode _eResultCode);
	~LoginResultPacket();

	LoginResultPacket(const LoginResultPacket& _other) = delete;
	LoginResultPacket(LoginResultPacket&& _other) = delete;

protected:
	LoginResultPacket& operator=(const LoginResultPacket& _other) = delete;
	LoginResultPacket& operator=(const LoginResultPacket&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ServerSerializer& _serializer) override;
	virtual void Deserialize(ServerSerializer& _serializer) override {};
};
