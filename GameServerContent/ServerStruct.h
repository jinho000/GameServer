#pragma once

class TCPSession;
struct UserInfo
{
	IPEndPoint					userEndPoint;
	std::shared_ptr<TCPSession> userTCPSession;
};
