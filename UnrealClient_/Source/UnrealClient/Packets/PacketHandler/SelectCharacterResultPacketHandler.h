#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"


// 용도 :
// 분류 :
// 첨언 :
class SelectCharacterResultPacketHandler : public PacketHandlerBase<SelectCharacterResultPacket>
{
public: // member Func
	void Start() override;
};

