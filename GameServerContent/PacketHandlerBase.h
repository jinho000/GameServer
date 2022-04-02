#pragma once
#include "PacketHeader.h"


// ��Ŷ�� ó���� �ڵ鷯�� �⺻ �θ� Ŭ����
template<class PacketType>
class PacketHandlerBase : public std::enable_shared_from_this<PacketHandlerBase<PacketType>>
{
protected: // member var
	PtrSTCPSession				m_TCPSession;
	std::shared_ptr<PacketType> m_packet;

public: // default
	template<class PacketType>
	PacketHandlerBase(PtrSTCPSession _TCPSession, std::shared_ptr<PacketType> _packet)
		: m_TCPSession(_TCPSession)
		, m_packet(_packet)
	{
	}

	~PacketHandlerBase() = default;

	PacketHandlerBase(const PacketHandlerBase & _other) = delete;
	PacketHandlerBase(PacketHandlerBase && _other) = delete;
	PacketHandlerBase& operator=(const PacketHandlerBase & _other) = delete;
	PacketHandlerBase& operator=(const PacketHandlerBase && _other) = delete;

public: // member Func
	virtual void Start() = 0;
};

