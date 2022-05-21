#pragma once
#include "PacketHandlerBase.h"

// 용도 :
// 분류 :
// 첨언 :
class PlayerComeInPacketHandler : public PacketHandlerBase<PlayerComeInPacket>
{
public: // member Func
	void Start() override;
};

