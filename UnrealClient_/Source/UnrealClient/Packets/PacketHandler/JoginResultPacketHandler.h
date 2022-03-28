#pragma once
#include "PacketHandlerBase.h"

// �뵵 :
// �з� :
// ÷�� :
class JoginResultPacketHandler : public PacketHandlerBase
{
private: // member var
	std::shared_ptr<JoginResultPacket> m_packet;

public: // default
	JoginResultPacketHandler(const std::shared_ptr<JoginResultPacket>& _packet);
	~JoginResultPacketHandler();

	JoginResultPacketHandler(const JoginResultPacketHandler& _other) = delete;
	JoginResultPacketHandler(JoginResultPacketHandler&& _other) = delete;
	
	JoginResultPacketHandler& operator=(const JoginResultPacketHandler& _other) = delete;
	JoginResultPacketHandler& operator=(const JoginResultPacketHandler&& _other) = delete;

private:

public: // member Func
	void Start();
};

