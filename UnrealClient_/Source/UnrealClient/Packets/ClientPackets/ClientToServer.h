#pragma once

#include "ClientPacketBase.h"
#include "CoreMinimal.h"

// 로그인 패킷
// 패킷 구성: [패킷타입] [ID] [Password]
class LoginPacket : public ClientPacketBase
{
private: // member var
	std::string m_id;
	std::string m_password;

public: // default
	LoginPacket()
		: ClientPacketBase(PacketType::LOGIN)
	{
	}

	LoginPacket(const FString& _id, const FString& _password)
		: ClientPacketBase(PacketType::LOGIN)
		, m_id(FTCHARToUTF8(*_id).Get())
		, m_password(FTCHARToUTF8(*_password).Get())
	{
	}

	~LoginPacket() = default;

	LoginPacket(const LoginPacket& _other) = delete;
	LoginPacket(LoginPacket&& _other) = delete;

protected:
	LoginPacket& operator=(const LoginPacket& _other) = delete;
	LoginPacket& operator=(const LoginPacket&& _other) = delete;

private:

public: // member Func
	virtual int SizeCheck()
	{
		return DataSizeCheck(m_id) + DataSizeCheck(m_password);
	}

	virtual void Serialize(ClientSerializer& _serializer) override
	{
		ClientPacketBase::Serialize(_serializer);
		_serializer << m_id;
		_serializer << m_password;
	}

	virtual void Deserialize(ClientSerializer& _serializer) override
	{}
};
