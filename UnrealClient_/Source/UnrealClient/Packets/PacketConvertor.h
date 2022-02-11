// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketBase.h"
#include <memory>
#include <vector>
/**
 * 
 */
// 패킷 변환기
class PacketConvertor
{
private: // member var
	std::shared_ptr<ClientPacketBase> m_packet;

public: // default
	PacketConvertor() = delete;
	PacketConvertor(const std::vector<uint8_t>& _buffer);
	~PacketConvertor();

	PacketConvertor(const PacketConvertor& _other) = delete;
	PacketConvertor(PacketConvertor&& _other) = delete;

protected:
	PacketConvertor& operator=(const PacketConvertor& _other) = delete;
	PacketConvertor& operator=(const PacketConvertor&& _other) = delete;

private:

public: // member Func
	std::shared_ptr<ClientPacketBase> GetPacket() { return m_packet; }

	template<class PacketType>
	std::shared_ptr<PacketType> GetPacket()
	{
		std::shared_ptr<PacketType> packet = std::dynamic_pointer_cast<PacketType>(m_packet);
		assert(nullptr != packet);

		return packet;
	}

	PacketType GetPacketType() { return m_packet->GetPacketType(); }
};
