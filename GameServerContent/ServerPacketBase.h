#pragma once
#include "ServerSerializer.h"
#include "PacketType.h"
#include "ContentStruct.h"
#include "ContentEnum.h"


// 서버에서 사용할 패킷 베이스
class ServerPacketBase
{
protected: // member var
	PacketType	m_packetType;
	UINT		m_size;

public: // default
	ServerPacketBase(PacketType _packetType)
		: m_packetType(_packetType)
		, m_size(-1)
	{
	}

	virtual ~ServerPacketBase() = default;

	ServerPacketBase(const ServerPacketBase& _other) = delete;
	ServerPacketBase(ServerPacketBase&& _other) = delete;
	ServerPacketBase& operator=(const ServerPacketBase& _other) = delete;
	ServerPacketBase& operator=(const ServerPacketBase&& _other) = delete;

public: // member Func

	// size 

	virtual int SizeCheck() = 0;

	unsigned int DataSizeCheck(const std::string& _Value)
	{
		// string은 문자열앞에 문자개수값이 존재
		return sizeof(int) + static_cast<unsigned int>(_Value.size());
	}

	template<typename Type>
	unsigned int DataSizeCheck(Type _Value)
	{
		return sizeof(_Value);
	}

	template<typename Type>
	unsigned int DataSizeCheck(std::vector<Type>& _Value)
	{
		int Size = 0;
		for (size_t i = 0; i < _Value.size(); i++)
		{
			Size += _Value[i].GetDataSize();
		}
		return Size;
	}

	// Serialize

	virtual void Serialize(ServerSerializer& _Serializer)
	{
		_Serializer.WriteEnum<PacketType>(m_packetType);
		_Serializer << SizeCheck();
	}
	virtual void operator>>(ServerSerializer& _serializer)
	{
		Serialize(_serializer);
	}

	
	// Deserialize

	virtual void Deserialize(ServerSerializer& _Serializer)
	{
		_Serializer.ReadEnum<PacketType>(m_packetType);
		_Serializer >> m_size;
	}
	virtual void operator<<(ServerSerializer& _serializer)
	{
		Deserialize(_serializer);
	}


	PacketType GetPacketType() { return m_packetType; }
};

