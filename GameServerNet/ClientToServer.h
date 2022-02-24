#pragma once
#include "ServerPacketBase.h"

// 클라이언트에서 전달한 로그인 패킷
class LoginPacket : public ServerPacketBase
{
public: // member var
	std::string m_id;
	std::string m_password;

public: // default
	LoginPacket()
		: ServerPacketBase(PacketType::LOGIN)
		, m_id()
		, m_password()
	{}

	~LoginPacket() = default;

	LoginPacket(const LoginPacket& _other) = delete;
	LoginPacket(LoginPacket&& _other) = delete;

protected:
	LoginPacket& operator=(const LoginPacket& _other) = delete;
	LoginPacket& operator=(const LoginPacket&& _other) = delete;

private:


public: // member Func
	virtual int SizeCheck() override
	{
		return DataSizeCheck(m_id) + DataSizeCheck(m_password);
	}

	virtual void Serialize(ServerSerializer& _serializer) override {};
	virtual void Deserialize(ServerSerializer& _serializer) override
	{
		ServerPacketBase::Deserialize(_serializer);

		_serializer >> m_id;
		_serializer >> m_password;
	}
};

