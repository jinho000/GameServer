#pragma once
#include "PacketHandlerBase.h"

class RequestMathPacketHandler : public PacketHandlerBase<RequestMathPacket>
{
public: // member Func
	void Start() override;
};


