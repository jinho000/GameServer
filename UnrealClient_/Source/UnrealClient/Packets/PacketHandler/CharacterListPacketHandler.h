#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"


class CharacterListPacketHandler : public PacketHandlerBase<CharacterListPacket>
{
public: // member Func
	void Start() override;

};

