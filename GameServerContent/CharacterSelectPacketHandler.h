#pragma once
#include "PacketHandlerBase.h"

// �뵵 :
// �з� :
// ÷�� :
class CharacterSelectPacketHandler : public PacketHandlerBase<CharacterSelectPacket>
{
public: // member Func
	void Start() override;
};

