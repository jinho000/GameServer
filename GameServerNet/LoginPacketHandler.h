#pragma once
#include "ServerToClient.h"
#include "ClientToServer.h"
#include "ServerAndClient.h"

// �α��� ��Ŷó�� �Լ� Ŭ����
// �α��� ���� ó���� �Լ��� �ϳ��� Ŭ������ ��� ����
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
	void DBCheck(); // dbó��
	void ResultSend(); // ��� ����

public: // member Func
	void Start();

};

