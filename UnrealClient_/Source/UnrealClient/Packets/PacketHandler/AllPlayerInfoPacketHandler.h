#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// �α��� ��� ��Ŷ�� ó���ϱ� ���� �ڵ鷯
class AllPlayerInfoPacketHandler : public PacketHandlerBase<AllPlayerInfoPacket>
{
public: // member Func
	void Start() override;
};

