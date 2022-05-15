#include "pch.h"
#include "UDPPacketDispatcher.h"
#include "PacketHandlerHeader.h"
#include "PacketHeader.h"

UDPPacketDispatcher::UDPPacketDispatcher()
{
	RegistHandler();
}

UDPPacketDispatcher::~UDPPacketDispatcher()
{
}

void UDPPacketDispatcher::RegistHandler()
{
	AddHandler(PacketType::PlayerUpdate, std::bind(&ProcessHandler<PlayerUpdatePacket, PlayerUpdatePacketHandler>, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	AddHandler(PacketType::UDPStart, std::bind(&ProcessHandler<UDPStartPacket, UDPStartPacketHandler>, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}
