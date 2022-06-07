#pragma once
#include <GameServerCore/ServerCore.h>
#include "PacketDispatcher.h"
#include "UDPPacketDispatcher.h"
#include "ClientPlayer.h"
#include "ServerPacketBase.h"

// 용도 :
// 분류 :
// 첨언 :
class ContentCore : public ServerCore
{
private: // member var
	static PacketDispatcher<TCPSession>	TcpDispatcher;
	static UDPPacketDispatcher			UdpDispatcher;
	
public:
	ContentCore() = default;
	~ContentCore() = default;

public: // default
	ContentCore(const ContentCore& _other) = delete;
	ContentCore(ContentCore&& _other) = delete;
	ContentCore& operator=(const ContentCore& _other) = delete;
	ContentCore& operator=(const ContentCore&& _other) = delete;

protected:
	static void AcceptEvent(std::shared_ptr<TCPSession> _tcpSession);
	static void RecvEvent(std::shared_ptr<TCPSession> _tcpSession, const std::vector<unsigned char>& _recBuffer);
	static void CloseEvent(std::shared_ptr<TCPSession> _tcpSession);
	static void UDPRecvEvent(std::shared_ptr<UDPSession> _udpSession, const std::vector<unsigned char>& _recvBuffer, IPEndPoint& _clientEndPoint);

public: // member Func
	void UserStart();
	void UserEnd();
};

