#pragma once
#include "IPEndPoint.h"
#include <GameServerBase/ServerBaseObject.h>
#include <GameServerBase/ServerQueue.h>
#include "UDPSendOverlapped.h"

class UDPSession;
using RecvCallBack = std::function<void(std::shared_ptr<UDPSession>, const std::vector<unsigned char>&, IPEndPoint&)>;

// UDP통신을 위한 세션
class UDPRecvOverlapped;
class UDPSession : public ServerBaseObject
{
private: // member var
	IPEndPoint	m_localAddr;
	SOCKADDR_IN	m_remoteAddr;
	SOCKET		m_sessionSocket;

	using UDPIOCallback = std::function<void(BOOL, DWORD, LPOVERLAPPED)>;
	UDPIOCallback	m_UDPIOCallback; // 세션소켓 IO이벤트 발생시 호출함수 함수객체
	
	RecvCallBack	m_recvCallBack; // 클라이언트의 리시브 데이터 처리함수

	// recvOverlapped 동기화처리?
	UDPRecvOverlapped* m_recvOveralpped;

	// 동시에 send를 하기위해 큐를 sendpool처럼 사용
	std::queue<UDPSendOverlapped*> m_sendPool;
	std::mutex m_sendPoolMutex;

	// WSARecvFrom err
	DWORD	flag;
	int		addrSize;

public: // default
	UDPSession(const IPEndPoint& _ipEndPoint);
	~UDPSession();

	UDPSession(const UDPSession& _other) = delete;
	UDPSession(UDPSession&& _other) = delete;
	UDPSession& operator=(const UDPSession& _other) = delete;
	UDPSession& operator=(const UDPSession&& _other) = delete;

private:
	// UPD IO 이벤트 발생시 호출될 함수
	static void OnIOCallBack(BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped);

public: // member Func

	// iocp workqueue에 소켓등록
	bool BindQueue(const ServerQueue& _workQueue);

	// 리시브 요청
	void RequestRecv();

	// recvFrom으로 데이터가 들어올경우 recv overlapped에서 호출되는 함수
	void OnRecv(const char* _data, DWORD _byteSize);

	void SetRecvCallBack(RecvCallBack _recvCallback);

	// EndPoint
	const IPEndPoint& GetEndPoint() { return m_localAddr; }

	// Send
	void Send(const std::vector<unsigned char>& _buffer, const IPEndPoint& _userEndPoint);
	void OnSendComplete(UDPSendOverlapped* _sendOverlapped);
};
