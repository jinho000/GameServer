#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// 
class UDPStartResultPacketHandler : public PacketHandlerBase<UDPStartResultPacket>
{
public: // member Func
	void Start() override;
};

