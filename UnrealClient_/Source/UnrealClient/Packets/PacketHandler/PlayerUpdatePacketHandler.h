#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"


class PlayerUpdatePacketHandler : public PacketHandlerBase<PlayerUpdatePacket>
{
public: // member Func
	void Start() override;

};

