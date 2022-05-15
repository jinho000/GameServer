#pragma once
#include "PacketType.h"
#include "ServerPacketBase.h"
#include "PacketConvertor.h"

// 용도 :
// 분류 :
// 첨언 :
class UDPPacketDispatcher
{
	using PacketHandler = std::function<void(std::shared_ptr<UDPSession>, std::shared_ptr<ServerPacketBase>, const IPEndPoint&)>;

private: // member var
	std::unordered_map<PacketType, PacketHandler> m_handlers;

public: // default
	UDPPacketDispatcher();
	~UDPPacketDispatcher();

	UDPPacketDispatcher(const UDPPacketDispatcher& _other) = delete;
	UDPPacketDispatcher(UDPPacketDispatcher&& _other) = delete;
	UDPPacketDispatcher& operator=(const UDPPacketDispatcher& _other) = delete;
	UDPPacketDispatcher& operator=(const UDPPacketDispatcher&& _other) = delete;

private: // member Func
	void AddHandler(PacketType _packetType, const PacketHandler& _handler)
	{
		m_handlers.insert(std::make_pair(_packetType, _handler));
	}

	void RegistHandler();

public:
	void Dispatch(const std::vector<unsigned char>& _recBuffer, PtrSUDPSession _UDPSession, const IPEndPoint& _clientEndPoint)
	{
		// UDP는 데이터가 한번에 옴
		PacketConvertor convert(_recBuffer);
		auto iter = m_handlers.find(convert.GetPacketType());
		assert(iter != m_handlers.end());

		const PacketHandler& handler = iter->second;
		handler(_UDPSession, convert.GetPacket(), _clientEndPoint);
	}

	template<class PacketType, class PacketHandler>
	static void ProcessHandler(PtrSUDPSession _session, std::shared_ptr<ServerPacketBase> _packet, const IPEndPoint& _endPoint)
	{
		// 패킷 변환
		std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType> (_packet);
		assert(nullptr != packet);

		// handler 처리 시작
		std::shared_ptr<PacketHandler> handler = std::make_shared<PacketHandler>();
		handler->InitUDP(_session, packet, _endPoint);
		handler->Start();
	}
};

