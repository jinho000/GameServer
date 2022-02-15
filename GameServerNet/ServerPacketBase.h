#pragma once
#include "ServerSerializer.h"
#include "PacketType.h"


// �������� ����� ��Ŷ ���̽�
class ServerPacketBase
{
protected: // member var
	PacketType m_packetType;

public: // default
	ServerPacketBase() = delete;
	ServerPacketBase(PacketType _packetType);
	virtual ~ServerPacketBase();

	ServerPacketBase(const ServerPacketBase& _other) = delete;
	ServerPacketBase(ServerPacketBase&& _other) = delete;

protected:
	ServerPacketBase& operator=(const ServerPacketBase& _other) = delete;
	ServerPacketBase& operator=(const ServerPacketBase&& _other) = delete;

private:

public: // member Func
	virtual void Serialize(ServerSerializer& _serializer) = 0 {};
	virtual void operator>>(ServerSerializer& _serializer);

	virtual void Deserialize(ServerSerializer& _serializer) = 0 {};
	virtual void operator<<(ServerSerializer& _serializer);

	PacketType GetPacketType() { return m_packetType; }
};

