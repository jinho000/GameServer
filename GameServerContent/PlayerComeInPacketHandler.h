#pragma once
#include "PacketHandlerBase.h"

// �뵵 :
// �з� :
// ÷�� :
class PlayerComeInPacketHandler : public PacketHandlerBase<PlayerComeInPacket>
{
public: // member Func
	void Start() override;
};

