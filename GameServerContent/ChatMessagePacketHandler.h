#pragma once
#include "PacketHandlerBase.h"

class ChatMessagePacketHandler : public PacketHandlerBase<ChatMessagePacket>
{
public: // member Func
	void Start();
};

