#pragma once
#include "PacketHeader.h"


// 패킷을 처리할 핸들러의 기본 부모 클래스
template<class PacketType>
class PacketHandlerBase : public std::enable_shared_from_this<PacketHandlerBase<PacketType>>
{
protected: // member var
	PtrSTCPSession				m_TCPSession;
	std::shared_ptr<PacketType> m_packet;

public: // member Func
	void Init(PtrSTCPSession _TCPSession, std::shared_ptr<PacketType> _packet);
	virtual void Start() = 0;
};

template<class PacketType>
inline void PacketHandlerBase<PacketType>::Init(PtrSTCPSession _TCPSession, std::shared_ptr<PacketType> _packet)
{
	m_TCPSession = _TCPSession;
	m_packet = _packet;
}
