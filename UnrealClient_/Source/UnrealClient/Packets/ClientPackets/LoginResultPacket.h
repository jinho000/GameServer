#pragma once
#include "ClientPacketBase.h"
#include "PacketType.h"


class LoginResultPacket : public ClientPacketBase
{
private: // member var
	EResultCode m_resultCode;

public: // default
	LoginResultPacket();
	~LoginResultPacket();

	LoginResultPacket(const LoginResultPacket& _other) = delete;
	LoginResultPacket(LoginResultPacket&& _other) = delete;

protected:
	LoginResultPacket& operator=(const LoginResultPacket& _other) = delete;
	LoginResultPacket& operator=(const LoginResultPacket&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ClientSerializer& _serializer) override;
	virtual void Deserialize(ClientSerializer& _serializer) override;

public:
	EResultCode GetResultCode() { return m_resultCode; }
};

