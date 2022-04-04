#pragma once
#include "PacketHandlerBase.h"

// 용도 :
// 분류 :
// 첨언 :
class CharacterSelectPacketHandler : public PacketHandlerBase<CharacterSelectPacket>
{
public: // member Func
	void Start() override;
};

