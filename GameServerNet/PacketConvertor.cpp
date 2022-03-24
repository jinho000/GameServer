#include "pch.h"
#include "PacketConvertor.h"
#include "ServerSerializer.h"
#include "Packets.h"

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
	case PacketType::LoginResult:
		m_packet = std::make_shared<LoginResultPacket>();
		break;
	case PacketType::ChatMessage:
		m_packet = std::make_shared<ChatMessagePacket>();
		break;
	default:
		return;
	}

	*m_packet << sr;
}
