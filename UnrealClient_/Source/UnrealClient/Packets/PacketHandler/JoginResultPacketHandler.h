#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// 용도 :
// 분류 :
// 첨언 :
class JoginResultPacketHandler : public PacketHandlerBase<JoginResultPacket>
{
public: // member Func
	void Start() override;
};

