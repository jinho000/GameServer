#pragma once
#include "PacketHandlerBase.h"
#include "UserTable.h"

// 로그인 패킷처리 함수 클래스
// 로그인 관련 처리의 함수를 하나의 클래스에 모아 놓음
class LoginPacketHandler : public PacketHandlerBase<LoginPacket>
{
private:
	LoginResultPacket			m_loginResultPacket;
	CharacterListPacket			m_CharacterListPacket;
	std::shared_ptr<UserRow>	m_userData;

private:
	void DBThreadCheckLogin();			// 로그인 디비 체크
	void NetThreadSendLoginResult();	// 로그인 결과 전송
	void DBThreadCheckCharList();		// 유저의 캐릭터 정보 가져오기
	void NetThreadSendCharList();		// 유저의 캐릭터 정보 전송

public: // member Func
	void Start();

};

