#pragma once
#include "ServerPacketBase.h"

template <class Session>
using PacketHandler = std::function<void(std::shared_ptr<Session>, std::shared_ptr<ServerPacketBase>)>;

// 각 패킷마다 타입이 존재
// 패킷 타입에 따라 어떤 함수로 처리할지 연결시켜줌
template <class Session>
class PacketDispatcher
{
private: // member var
	std::unordered_map<PacketType, PacketHandler<Session>> m_handlers;

public: // default
	PacketDispatcher() = default;
	~PacketDispatcher() = default;

	PacketDispatcher(const PacketDispatcher& _other) = delete;
	PacketDispatcher(PacketDispatcher&& _other) = delete;

protected:
	PacketDispatcher& operator=(const PacketDispatcher& _other) = delete;
	PacketDispatcher& operator=(const PacketDispatcher&& _other) = delete;

private:

public: // member Func
	void AddHandler(PacketType _packetType, PacketHandler<Session>& _handler)
	{
		m_handlers.insert(std::make_pair(_packetType, _handler));
	}

	const PacketHandler<Session>& GetHandler(PacketType _packetType)
	{
		auto iter = m_handlers.find(_packetType);
		return iter->second;
	}
};

