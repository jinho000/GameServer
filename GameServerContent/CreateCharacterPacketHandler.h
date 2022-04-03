#pragma once
#include <GameServerContent/ServerAndClient.h>
#include "PacketHandlerBase.h"
// 용도 :
// 분류 :
// 첨언 :
class CreateCharacterPacketHandler : public PacketHandlerBase<CreateCharacterPacket>
{
private: // member var
	CreateCharacterResultPacket m_resultPacket;

private:
	void DBThreadWork();
	void NetThreadSendResult();

public: // member Func
	void Start();
};

