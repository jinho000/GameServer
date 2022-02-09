#pragma once
#include "ServerPacketBase.h"
#include "ServerSerializer.h"

// �������� ����� �α��� ��Ŷ
class LoginPacket : public ServerPacketBase
{
public: // member var
	std::string m_id;
	std::string m_password;

public: // default
	LoginPacket();
	~LoginPacket();

	LoginPacket(const LoginPacket& _other) = delete;
	LoginPacket(LoginPacket&& _other) = delete;

protected:
	LoginPacket& operator=(const LoginPacket& _other) = delete;
	LoginPacket& operator=(const LoginPacket&& _other) = delete;

private:


public: // member Func
	virtual void Serialize(ServerSerializer& _serializer) {};
	virtual void Deserialize(ServerSerializer& _serializer) override;
};

