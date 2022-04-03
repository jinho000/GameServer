#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

class CreateCharacterResultPacketHandler : public PacketHandlerBase<CreateCharacterResultPacket>
{
public: // member Func
	void Start() override;
};

