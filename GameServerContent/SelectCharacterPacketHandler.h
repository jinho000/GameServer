#pragma once
#include "PacketHandlerBase.h"

// 용도 :
// 분류 :
// 첨언 :
class SelectCharacterPacketHandler : public PacketHandlerBase<SelectCharacterPacket>
{
private:
	SelectCharacterResultPacket m_resultPacket;
	FCharacterInfo				m_selectCharacter;

private:
	void DBThreadCheckSelectCharacter();	// 선택한 캐릭터 디비체크
	void NetThreadSendSelectResult();		// 결과 전송
	void InsertUserToSection();

public: // member Func
	void Start() override;
};

