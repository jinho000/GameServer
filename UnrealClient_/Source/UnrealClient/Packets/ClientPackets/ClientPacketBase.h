#pragma once
#include "../ClientSerializer.h"
#include "PacketType.h"

// Ŭ���̾�Ʈ���� ����� ��Ŷ�� �⺻ Ŭ����
class ClientPacketBase
{
protected: // member var
	PacketType			m_packetType;

	
public: // default
	ClientPacketBase() = delete;
	ClientPacketBase(PacketType _packetType);
	virtual ~ClientPacketBase();

	ClientPacketBase(const ClientPacketBase& _other) = delete;
	ClientPacketBase(ClientPacketBase&& _other) = delete;

protected:
	ClientPacketBase& operator=(const ClientPacketBase& _other) = delete;
	ClientPacketBase& operator=(const ClientPacketBase&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ClientSerializer& _serializer) = 0 {};
	virtual void operator>>(ClientSerializer& _serializer);

	virtual void Deserialize(ClientSerializer& _serializer) = 0 {};
	virtual void operator<<(ClientSerializer& _serializer);

	PacketType GetPacketType() { return m_packetType; }
};
