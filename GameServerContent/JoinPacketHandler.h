#pragma once
#include "PacketHandlerBase.h"

class JoinPacketHandler : public PacketHandlerBase<JoinPacket>
{
private:
	void DBThreadRequestJoin();

public: // member Func
	void Start();
};

