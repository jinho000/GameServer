#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// �α��� ��� ��Ŷ�� ó���ϱ� ���� �ڵ鷯
class PlayerComeInPacketHandler : public PacketHandlerBase<PlayerComeInPacket>
{
public: // member Func
	void Start() override;
};

