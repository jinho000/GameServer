#pragma once
#include "ServerPacketBase.h"
#include "ServerToClient.h"
#include "ClientToServer.h"
#include "ServerAndClient.h"
#include "PacketHandlerHeader.h"

template <class Session>
using PacketHandler = std::function<void(std::shared_ptr<Session>, std::shared_ptr<ServerPacketBase>)>;

// 각 패킷마다 타입이 존재
// 패킷 타입에 따라 어떤 함수로 처리할지 연결시켜줌
// 여러 패킷 처리에 대한 핸들러를 하나로 모아 정리 시켜줌
//

template <class Session>
class PacketDispatcher
{
private: // member var
	std::unordered_map<PacketType, PacketHandler<Session>> m_handlers;

public: // default
	PacketDispatcher();
	~PacketDispatcher() = default;

	PacketDispatcher(const PacketDispatcher& _other) = delete;
	PacketDispatcher(PacketDispatcher&& _other) = delete;

protected:
	PacketDispatcher& operator=(const PacketDispatcher& _other) = delete;
	PacketDispatcher& operator=(const PacketDispatcher&& _other) = delete;

private:

public: // member Func
	void AddHandler(PacketType _packetType, const PacketHandler<Session>& _handler)
	{
		m_handlers.insert(std::make_pair(_packetType, _handler));
	}

	const PacketHandler<Session>& GetHandler(PacketType _packetType)
	{
		auto iter = m_handlers.find(_packetType);

		// 패킷에 대한 핸들러가 등록되어 있어야함
		assert(iter != m_handlers.end());

		return iter->second;
	}

	template<class PacketType, class PacketHandler>
	static void ProcessHandler(PtrSTCPSession _s, PtrSPacketBase _packet)
	{
		// 패킷 변환
		std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType> (_packet);
		assert(nullptr != packet);

		// handler 처리 시작
		std::shared_ptr<PacketHandler> handler = std::make_shared<PacketHandler>(_s, packet);
		handler->Start();
	}
};

#include "RegistHandlerToDispatcher.h"
