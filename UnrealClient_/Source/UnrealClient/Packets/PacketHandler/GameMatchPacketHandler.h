#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"
// 용도 :
// 분류 :
// 첨언 :
class GameMatchPacketHandler : public PacketHandlerBase<GameMatchPacket>
{
public:
	void Start() override;
};

