#pragma once
#include "ClientPacketBase.h"
#include "CoreMinimal.h"

// �α��� ��Ŷ
// ��Ŷ ����: [��ŶŸ��] [ID] [Password]
class LoginPacket : public ClientPacketBase
{
private: // member var
	std::string m_id;
	std::string m_password;

public: // default
	LoginPacket(const FString& _id, const FString& _password);
	~LoginPacket();

	LoginPacket(const LoginPacket& _other) = delete;
	LoginPacket(LoginPacket&& _other) = delete;

protected:
	LoginPacket& operator=(const LoginPacket& _other) = delete;
	LoginPacket& operator=(const LoginPacket&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ClientSerializer& _serializer);
	virtual void Deserialize(ClientSerializer& _serializer);
};