#include "PacketConvertor.h"
#include "ClientPackets/ServerSerializer.h"
#include "ClientPackets/Packets.h"

PacketConvertor::PacketConvertor(const std::vector<unsigned char>&_buffer)
	: m_packet(nullptr)
{
	ServerSerializer sr(_buffer);

	PacketType type;
	memcpy_s(&type, sizeof(PacketType), _buffer.data(), sizeof(PacketType));
	switch (type)
	{
	case PacketType::Login:
		m_packet = std::make_shared<LoginPacket>();
		break;
	case PacketType::Join:
		m_packet = std::make_shared<JoinPacket>();
		break;
	case PacketType::LoginResult:
		m_packet = std::make_shared<LoginResultPacket>();
		break;
	case PacketType::JoginResult:
		m_packet = std::make_shared<JoginResultPacket>();
		break;
	case PacketType::ChatMessage:
		m_packet = std::make_shared<ChatMessagePacket>();
		break;
	default:
		return;
	}

	*m_packet << sr;
}
