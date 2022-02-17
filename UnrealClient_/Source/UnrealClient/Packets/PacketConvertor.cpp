// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketConvertor.h"
#include "ClientSerializer.h"
#include "ClientPackets/LoginPacket.h"
#include "ClientPackets/LoginResultPacket.h"
#include "ClientPackets/ChatMessagePacket.h"

PacketConvertor::PacketConvertor(const std::vector<uint8_t>& _buffer)
	: m_packet(nullptr)
{
	ClientSerializer sr(_buffer);

	PacketType type;
	memcpy_s(&type, sizeof(PacketType), _buffer.data(), sizeof(PacketType));
	switch (type)
	{
	case PacketType::LOGIN:
	{
		m_packet = std::make_shared<LoginPacket>();
		*m_packet << sr;
		break;
	}
	case PacketType::LOGIN_RESULT:
	{
		m_packet = std::make_shared<LoginResultPacket>();
		*m_packet << sr;
		break;
	}
	case PacketType::CHAT_MESSAGE:
	{
		m_packet = std::make_shared<ChatMessagePacket>();
		*m_packet << sr;
		break;
	}
	default:
		// 패킷 타입 처리 필요
		check(false);
		break;
	}
}

PacketConvertor::~PacketConvertor()
{
}

