#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

class DeleteCharacterResultPacketHandler : public PacketHandlerBase<DeleteCharacterResultPacket>
{
public: // member Func
	void Start() override;
};

