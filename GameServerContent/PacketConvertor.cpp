#include "pch.h"
#include "PacketConvertor.h"
#include "ServerSerializer.h"
#include "PacketHeader.h"

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
	case PacketType::CreateCharacter:
		m_packet = std::make_shared<CreateCharacterPacket>();
		break;
	case PacketType::SelectCharacter:
		m_packet = std::make_shared<SelectCharacterPacket>();
		break;
	case PacketType::LoginResult:
		m_packet = std::make_shared<LoginResultPacket>();
		break;
	case PacketType::JoginResult:
		m_packet = std::make_shared<JoginResultPacket>();
		break;
	case PacketType::CharacterList:
		m_packet = std::make_shared<CharacterListPacket>();
		break;
	case PacketType::CreateCharacterResult:
		m_packet = std::make_shared<CreateCharacterResultPacket>();
		break;
	case PacketType::SelectCharacterResult:
		m_packet = std::make_shared<SelectCharacterResultPacket>();
		break;
	case PacketType::InsertSectionResult:
		m_packet = std::make_shared<InsertSectionResultPacket>();
		break;
	case PacketType::ChatMessage:
		m_packet = std::make_shared<ChatMessagePacket>();
		break;
	default:
		return;
	}

	*m_packet << sr;
}
