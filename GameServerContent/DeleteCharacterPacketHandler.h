#pragma once
#include <GameServerContent/ServerAndClient.h>
#include "PacketHandlerBase.h"
// 용도 :
// 분류 :
// 첨언 :
class DeleteCharacterPacketHandler : public PacketHandlerBase<DeleteCharacterPacket>
{
private: // member var
	DeleteCharacterResultPacket m_resultPacket;

private:
	void DBThreadWork();
	void NetThreadSendResult();

public: // member Func
	void Start() override;
};

