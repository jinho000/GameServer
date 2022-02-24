#pragma once
#include "ClientPacketBase.h"


class LoginResultPacket : public ClientPacketBase
{
private: // member var
	EResultCode m_resultCode;

public: // default
	LoginResultPacket()
		: ClientPacketBase(PacketType::LOGIN_RESULT)
		, m_resultCode(EResultCode::NONE)
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
	virtual int SizeCheck()
	{
		return DataSizeCheck(m_resultCode);
	}

	virtual void Serialize(ClientSerializer& _serializer) override
	{}

	virtual void Deserialize(ClientSerializer& _serializer) override
	{
		ClientPacketBase::Deserialize(_serializer);
		_serializer.ReadEnum(m_resultCode);
	}



public:
	EResultCode GetResultCode() { return m_resultCode; }
};

