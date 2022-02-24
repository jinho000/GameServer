#pragma once
#include "../ClientSerializer.h"
#include "PacketType.h"

// Ŭ���̾�Ʈ���� ����� ��Ŷ�� �⺻ Ŭ����
class ClientPacketBase
{
protected: // member var
	PacketType			m_packetType;
	UINT				m_size;
	
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
	virtual int SizeCheck() = 0;

	unsigned int DataSizeCheck(const std::string& _Value)
	{
		// string�� ���ڿ��տ� ���ڰ������� ����
		return sizeof(int) + static_cast<unsigned int>(_Value.size());
	}

	template<typename Type>
	unsigned int DataSizeCheck(Type _Value)
	{
		return sizeof(_Value);
	}

	virtual void Serialize(ClientSerializer& _Serializer)
	{
		_Serializer.WriteEnum<PacketType>(m_packetType);
		_Serializer << SizeCheck();
	}
	virtual void operator>>(ClientSerializer& _serializer)
	{
		Serialize(_serializer);
	}


	virtual void Deserialize(ClientSerializer& _Serializer)
	{
		_Serializer.ReadEnum<PacketType>(m_packetType);
		_Serializer >> m_size;
	}
	virtual void operator<<(ClientSerializer& _serializer)
	{
		Deserialize(_serializer);
	}

	PacketType GetPacketType() { return m_packetType; }
};
