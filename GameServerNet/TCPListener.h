#pragma once
#include <GameServerBase/ServerBaseObject.h>
#include "IPEndPoint.h"
#include "GameServerBase/ServerQueue.h"

// 용도 : 소켓에 대한 클라의 접속을 받아들이는 클래스
// 분류 :
// 첨언 : 접속 확인은 비동기로 처리
class ServerQueue;
class TCPSession;
class TCPListener : public ServerBaseObject
{
	friend class TCPSession;

private: // member var
	SOCKET												m_listenerSocket;
	IPEndPoint											m_ipEndPoint;
	ServerQueue											m_pJobQueue;
	std::function<void(std::shared_ptr<TCPSession>)>	m_acceptCallback;
	
	std::deque<std::shared_ptr<TCPSession>>				m_connectionPool;
	std::mutex											m_connectPoolLock;

	std::unordered_map<__int64, std::shared_ptr<TCPSession>>	m_connections;
	std::mutex													m_connecsLock;

public: // default
	TCPListener() = delete;
	TCPListener(const IPEndPoint& _EndPoint, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback);
	TCPListener(const std::string& _ip, int _port, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback);
	~TCPListener();

	TCPListener(const TCPListener& _other) = delete;
	TCPListener(TCPListener&& _other) = delete;

protected:
	TCPListener& operator=(const TCPListener& _other) = delete;
	TCPListener& operator=(const TCPListener&& _other) = delete;

private:
	void Initialize(const IPEndPoint& _EndPoint);
	void StartAccept(UINT _backLog);
	void AsyncAccept();
	void OnAccept(BOOL _result, DWORD _byteSize, LPOVERLAPPED _overlapped);

	void CloseSession(PtrSTCPSession _tcpSession);

	// listen 소켓 종료
	void CloseSocket();

public: // member Func
	void BroadCast(const std::vector<uint8_t>& _buffer, PtrSTCPSession _requestSession);
	void BroadCast(const std::vector<uint8_t>& _buffer);

};

