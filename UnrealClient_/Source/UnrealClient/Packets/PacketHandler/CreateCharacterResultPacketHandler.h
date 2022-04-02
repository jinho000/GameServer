#pragma once
#include "PacketHandlerBase.h"

class CreateCharacterResultPacketHandler : public PacketHandlerBase
{
private: // member var
	std::shared_ptr<CreateCharacterResultPacket> m_packet;

public: // default
	CreateCharacterResultPacketHandler(const std::shared_ptr<CreateCharacterResultPacket>& _packet);
	~CreateCharacterResultPacketHandler();

	CreateCharacterResultPacketHandler(const CreateCharacterResultPacketHandler& _other) = delete;
	CreateCharacterResultPacketHandler(CreateCharacterResultPacketHandler&& _other) = delete;
	CreateCharacterResultPacketHandler& operator=(const CreateCharacterResultPacketHandler& _other) = delete;
	CreateCharacterResultPacketHandler& operator=(const CreateCharacterResultPacketHandler&& _other) = delete;

private:

public: // member Func
	void Start() override;
};

