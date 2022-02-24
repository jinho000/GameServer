#pragma once
#include "ServerToClient.h"
#include "ClientToServer.h"
#include "ServerAndClient.h"

// 로그인 패킷처리 함수 클래스
// 로그인 관련 처리의 함수를 하나의 클래스에 모아 놓음
class LoginPacketHandler
{
private: // member var
	PtrSTCPSession	m_TCPSession;
	PtrSLoginPacket m_packet;

public: // default
	LoginPacketHandler() = delete;
	LoginPacketHandler(PtrSTCPSession _TCPSession, PtrSLoginPacket _packet);
	~LoginPacketHandler();

	LoginPacketHandler(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler(LoginPacketHandler&& _other) = delete;

protected:
	LoginPacketHandler& operator=(const LoginPacketHandler& _other) = delete;
	LoginPacketHandler& operator=(const LoginPacketHandler&& _other) = delete;

private:
	void DBCheck(); // db처리
	void ResultSend(); // 결과 전송

public: // member Func
	void Start();

};

