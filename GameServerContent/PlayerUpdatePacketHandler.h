#pragma once
#include "PacketHandlerBase.h"
#include "PacketHeader.h"

// �뵵 :
// �з� :
// ÷�� :
class PlayerUpdatePacketHandler : public PacketHandlerBase<PlayerUpdatePacket>
{
public: // member Func
	void Start() override;
};

