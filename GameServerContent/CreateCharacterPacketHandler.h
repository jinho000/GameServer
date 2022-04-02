#pragma once
#include <GameServerContent/ServerAndClient.h>
#include "PacketHandlerBase.h"
// �뵵 :
// �з� :
// ÷�� :
class CreateCharacterPacketHandler : public PacketHandlerBase<CreateCharacterPacket>
{
private: // member var
	CreateCharacterResultPacket m_resultPacket;

public: // default
	CreateCharacterPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<CreateCharacterPacket> _packet);
	~CreateCharacterPacketHandler();

	CreateCharacterPacketHandler(const CreateCharacterPacketHandler& _other) = delete;
	CreateCharacterPacketHandler(CreateCharacterPacketHandler&& _other) = delete;
	CreateCharacterPacketHandler& operator=(const CreateCharacterPacketHandler& _other) = delete;
	CreateCharacterPacketHandler& operator=(const CreateCharacterPacketHandler&& _other) = delete;

private:
	void DBThreadWork();
	void NetThreadSendResult();

public: // member Func
	void Start();
};

