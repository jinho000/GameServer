#pragma once
#include "PacketHandlerBase.h"
#include "PacketHeader.h"

// 용도 :
// 분류 :
// 첨언 :
class PlayerUpdatePacketHandler : public PacketHandlerBase<PlayerUpdatePacket>
{
private:
	PtrSUDPSession						m_UDPSession;
	std::shared_ptr<PlayerUpdatePacket> m_UDPpacket;
	IPEndPoint							m_clientEndPoint;

public: // member Func
	void InitUDP(PtrSUDPSession _UDPSession, std::shared_ptr<PlayerUpdatePacket> _packet, const IPEndPoint& _clientEndPoint);
	void Start() override;
};


