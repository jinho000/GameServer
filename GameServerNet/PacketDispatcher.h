#pragma once
#include "ServerPacketBase.h"
#include "ServerToClient.h"
#include "ClientToServer.h"
#include "ServerAndClient.h"
#include "PacketHandlerHeader.h"

template <class Session>
using PacketHandler = std::function<void(std::shared_ptr<Session>, std::shared_ptr<ServerPacketBase>)>;

// �� ��Ŷ���� Ÿ���� ����
// ��Ŷ Ÿ�Կ� ���� � �Լ��� ó������ ���������
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

		// ��Ŷ�� ���� �ڵ鷯�� ��ϵǾ� �־����
		assert(iter != m_handlers.end());

		return iter->second;
	}

	template<class PacketType, class PacketHandler>
	static void ProcessHandler(PtrSTCPSession _s, PtrSPacketBase _packet)
	{
		// ��Ŷ ��ȯ
		std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType> (_packet);
		assert(nullptr != packet);

		// handler ó�� ����
		std::shared_ptr<PacketHandler> handler = std::make_shared<PacketHandler>(_s, packet);
		handler->Start();
	}
};

template<class Session>
PacketDispatcher<Session>::PacketDispatcher()
{
	int a = 0;
	// dispatcher�� ��Ŷ�� ó���� �Լ� �߰�
	//AddHandler(PacketType::Login, std::bind(&ProcessHandler<LoginPacket, LoginPacketHandler>, std::placeholders::_1, std::placeholders::_2));
	//AddHandler(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacket, ChatPacketHandler>, std::placeholders::_1, std::placeholders::_2));
}
