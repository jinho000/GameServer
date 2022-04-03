#pragma once
#include "PacketHandlerBase/PacketHandlerBase.h"

// 로그인 결과 패킷을 처리하기 위한 핸들러
class ChatMessagePacketHandler : public PacketHandlerBase<ChatMessagePacket>
{
public: // member Func
	void Start() override;
};

