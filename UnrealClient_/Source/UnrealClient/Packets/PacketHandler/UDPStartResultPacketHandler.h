#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// �α��� ��� ��Ŷ�� ó���ϱ� ���� �ڵ鷯
class UDPStartResultPacketHandler : public PacketHandlerBase<UDPStartResultPacket>
{
public: // member Func
	void Start() override;
};

