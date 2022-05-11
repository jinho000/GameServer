#pragma once
#include "PacketHandlerBase.h"
#include "PacketHeader.h"

// 용도 :
// 분류 :
// 첨언 :
class PlayerUpdatePacketHandler : public PacketHandlerBase<PlayerUpdatePacket>
{
public: // member Func
	void Start() override;
};

