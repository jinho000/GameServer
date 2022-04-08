#pragma once
#include "PacketHandlerBase.h"

class ChatMessagePacketHandler : public PacketHandlerBase<ChatMessagePacket>
{
private:
	void DBThreadCheckDB();
	void NetThreadSendResult();

public: // member Func
	void Start() override;
};

