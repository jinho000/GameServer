#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// 용도 :
// 분류 :
// 첨언 :
class InsertSectionResultPacketHandler : public PacketHandlerBase<InsertSectionResultPacket>
{
public: // member Func
	void Start() override;
};

