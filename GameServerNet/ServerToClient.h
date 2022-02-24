#pragma once
#include "ServerPacketBase.h"

// Ŭ���̾�Ʈ�� �α��� ��� ���� ��Ŷ
class LoginResultPacket : public ServerPacketBase
{
private: // member var
	EResultCode m_resultCode;

public: // default
	LoginResultPacket()
		: ServerPacketBase(PacketType::LOGIN_RESULT)
	{}

	LoginResultPacket(EResultCode _eResultCode)
		: ServerPacketBase(PacketType::LOGIN_RESULT)
		, m_resultCode(_eResultCode)
	{
	}

	~LoginResultPacket() = default;

	LoginResultPacket(const LoginResultPacket& _other) = delete;
	LoginResultPacket(LoginResultPacket&& _other) = delete;

protected:
	LoginResultPacket& operator=(const LoginResultPacket& _other) = delete;
	LoginResultPacket& operator=(const LoginResultPacket&& _other) = delete;

private:

public: // member Func
	virtual int SizeCheck() override
	{
		return DataSizeCheck(m_resultCode);
	}

	virtual void Serialize(ServerSerializer& _serializer) override
	{
		ServerPacketBase::Serialize(_serializer);
		_serializer.WriteEnum(m_resultCode);
	}

	virtual void Deserialize(ServerSerializer& _serializer) override {};
};
