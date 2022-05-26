#pragma once

class TCPSession;
class ClientPlayer;
struct UserInfo
{
	IPEndPoint						userEndPoint;
	std::shared_ptr<TCPSession>		userTCPSession;
	std::shared_ptr<ClientPlayer>	userCharacterInfo;
};
