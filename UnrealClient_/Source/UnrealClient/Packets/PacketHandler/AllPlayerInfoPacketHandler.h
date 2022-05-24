#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

class AllPlayerInfoPacketHandler : public PacketHandlerBase<AllPlayerInfoPacket>
{
public: // member Func
	void Start() override;
};

