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
	case PacketType::CreateCharacter:
		m_packet = std::make_shared<CreateCharacterPacket>();
		break;
	case PacketType::SelectCharacter:
		m_packet = std::make_shared<SelectCharacterPacket>();
		break;
	case PacketType::DeleteCharacter:
		m_packet = std::make_shared<DeleteCharacterPacket>();
		break;
	case PacketType::UDPStart:
		m_packet = std::make_shared<UDPStartPacket>();
		break;
	case PacketType::PlayerUpdate:
		m_packet = std::make_shared<PlayerUpdatePacket>();
		break;
	case PacketType::RequestMath:
		m_packet = std::make_shared<RequestMathPacket>();
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
	case PacketType::DeleteCharacterResult:
		m_packet = std::make_shared<DeleteCharacterResultPacket>();
		break;
	case PacketType::SelectCharacterResult:
		m_packet = std::make_shared<SelectCharacterResultPacket>();
		break;
	case PacketType::InsertSectionResult:
		m_packet = std::make_shared<InsertSectionResultPacket>();
		break;
	case PacketType::UDPStartResult:
		m_packet = std::make_shared<UDPStartResultPacket>();
		break;
	case PacketType::AllPlayerInfo:
		m_packet = std::make_shared<AllPlayerInfoPacket>();
		break;
	case PacketType::SpawnOtherPlayer:
		m_packet = std::make_shared<SpawnOtherPlayerPacket>();
		break;
	case PacketType::GameMatch:
		m_packet = std::make_shared<GameMatchPacket>();
		break;
	case PacketType::ChatMessage:
		m_packet = std::make_shared<ChatMessagePacket>();
		break;
	default:
		return;
	}

	*m_packet << sr;
}
