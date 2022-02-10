// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketConvertor.h"
#include "ClientSerializer.h"
#include "LoginPacket.h"

PacketConvertor::PacketConvertor(const std::vector<uint8_t>& _buffer)
	: m_packet(nullptr)
{
	PacketType type;
	memcpy_s(&type, sizeof(PacketType), _buffer.data(), sizeof(PacketType));
	switch (type)
	{
	case PacketType::LOGIN:
	{
		ClientSerializer sr(_buffer);
		m_packet = std::make_shared<LoginPacket>();
		*m_packet << sr;
		break;
	}
	default:
		break;
	}
}

PacketConvertor::~PacketConvertor()
{
}

