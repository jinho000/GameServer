#pragma once
#include "ServerPacketBase.h"
#include "PacketHeader.h"
#include "PacketConvertor.h"
#include "PacketHandlerHeader.h"

template <class Session>
using PacketHandler = std::function<void(std::shared_ptr<Session>, std::shared_ptr<ServerPacketBase>)>;

// 각 패킷마다 타입이 존재
// 패킷 타입에 따라 어떤 함수로 처리할지 연결시켜줌
// 여러 패킷 처리에 대한 핸들러를 하나로 모아 정리 시켜줌
//

// Handler dispacher
template <class Session>
class PacketDispatcher
{
private: // member var
	std::unordered_map<PacketType, PacketHandler<Session>> m_handlers;

public:
	PacketDispatcher();

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

	void Dispatch(const std::vector<unsigned char>& _recBuffer, PtrSTCPSession _TCPSession)
	{
		// TCP데이터 크기 확인 후 변환하기

		PacketConvertor convert(_recBuffer);
		const PacketHandler<TCPSession>& handler = GetHandler(convert.GetPacketType());
		handler(_TCPSession, convert.GetPacket());
	}

	template<class PacketType, class PacketHandler>
	static void ProcessHandler(PtrSTCPSession _session, std::shared_ptr<ServerPacketBase> _packet)
	{
		// 패킷 변환
		std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType> (_packet);
		assert(nullptr != packet);

		// handler 처리 시작
		std::shared_ptr<PacketHandler> handler = std::make_shared<PacketHandler>();
		handler->Init(_session, packet);
		handler->Start();
	}
};

#include "RegistHandlerToDispatcher.h"
