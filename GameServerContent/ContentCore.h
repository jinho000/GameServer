#pragma once
#include <GameServerCore/ServerCore.h>

// 용도 :
// 분류 :
// 첨언 :
class ContentCore : public ServerCore
{
private: // member var
	
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

public: // member Func
	void UserStart();
};

