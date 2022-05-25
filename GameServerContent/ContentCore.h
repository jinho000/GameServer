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
	static PacketDispatcher<TCPSession>					TcpDispatcher;
	static UDPPacketDispatcher							UdpDispatcher;
	
	// 세션만들기 전까지 유저 앤드포인트를 코어가 가진다(여러 스레드에서 동시 접근 가능)
	static std::mutex													UnserEndPointLock;
	static std::vector<IPEndPoint>										AllUserEndPoint;

	static std::mutex													ClientPlayerLock;
	static std::unordered_map<uint64_t, std::shared_ptr<ClientPlayer>>	AllClientPlayer;

public:
	ContentCore();
	~ContentCore();

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

public:
	// 세션으로 옮기기
	static void AddNewPlayer(const std::shared_ptr<ClientPlayer>& _clientPlayer);
	static void SetPlayerData(const FPlayerUpdateData& _playerUpdateData);

	static const std::unordered_map<uint64_t, std::shared_ptr<ClientPlayer>>& GetAllPlayer();

	static void SetUserEndPoint(const IPEndPoint& _userEndPoint);
	static const std::vector<IPEndPoint>& GetAllUserEndPoint() { return AllUserEndPoint; };

	static void BroadCastUDP(ServerPacketBase* _packet, UDPSession* _udpSession);
	static void BroadCastAllPlayerDataUDP(const std::shared_ptr<UDPSession>& _udpSession);

public: // member Func
	void UserStart();
	void UserEnd();
};

