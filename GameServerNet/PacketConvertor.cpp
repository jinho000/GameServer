#include "pch.h"
#include "PacketConvertor.h"
#include "ServerSerializer.h"
#include "ServerAndClient.h"
#include "ServerToClient.h"
#include "ClientToServer.h"

PacketConvertor::PacketConvertor(const std::vector<uint8_t>& _buffer)
	: m_packet(nullptr)
{
	PacketType type;
	memcpy_s(&type, sizeof(PacketType), _buffer.data(), sizeof(PacketType));
	switch (type)
	{
	case PacketType::LOGIN:
	{
		ServerSerializer sr(_buffer);
		m_packet = std::make_shared<LoginPacket>();
		*m_packet << sr;
		break;
	}
	case PacketType::CHAT_MESSAGE:
	{
		ServerSerializer sr(_buffer);
		m_packet = std::make_shared<ChatMessagePacket>();
		*m_packet << sr;
		break;
	}
	default:
		// 패킷 타입을 정하지 않은경우
		assert(nullptr); 
		break;
	}
}

PacketConvertor::~PacketConvertor()
{
}

