#pragma once
#include "Packets.h"

// 용도 :
// 분류 :
// 첨언 :
class JoinPacketHandler : public std::enable_shared_from_this<JoinPacketHandler>
{
private: // member var
	PtrSTCPSession						m_TCPSession;
	std::shared_ptr<JoinPacket>			m_packet;

public: // default
	JoinPacketHandler() = delete;;
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

