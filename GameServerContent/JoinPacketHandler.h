#pragma once
#include "PacketHandlerBase.h"

class JoinPacketHandler : public PacketHandlerBase<JoinPacket>
{
public: // default
	JoinPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<JoinPacket> _packet);
	~JoinPacketHandler();

	JoinPacketHandler(const JoinPacketHandler& _other) = delete;
	JoinPacketHandler(JoinPacketHandler&& _other) = delete;
	JoinPacketHandler& operator=(const JoinPacketHandler& _other) = delete;
	JoinPacketHandler& operator=(const JoinPacketHandler&& _other) = delete;

private:
	void DBThreadRequestJoin();

public: // member Func
	void Start();
};

