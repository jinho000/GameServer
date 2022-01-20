#pragma once
#include "IPEndPoint.h"
#include "GameServerBase/ServerBaseObject.h"
#include "GameServerBase/ServerQueue.h"

// 용도 : 서버와 클라의 연결
// 분류 :
// 첨언 : 
class RecvOverlapped;
class DisconnectOverlapped;
class TCPSession : public ServerBaseObject
{
private:
	// friend class
	friend class TCPListener;
	friend class RecvOverlapped;
	friend class DisconnectOverlapped;

private: // member var
	__int64			m_conectId;
	SOCKET			m_sessionSocket;
	//IPEndPoint	m_localAddr;
	//IPEndPoint	m_remoteAddr;

	RecvOverlapped*			m_recvOverlapped;
	DisconnectOverlapped*	m_disconOverlapped;

	using RecvCallBack = std::function<void(PtrSTCPSession, const std::vector<char>&)>;
	RecvCallBack			m_recvCallBack;

	using CloseCallBack = std::function<void(PtrSTCPSession)>;
	CloseCallBack			m_closeCallBack;

	std::atomic_bool		m_callClose;
	std::atomic_bool		m_bReuseSocket;

public: // default
	TCPSession();
	~TCPSession();

	TCPSession(const TCPSession& _other) = delete;
	TCPSession(TCPSession&& _other) = delete;

protected:
	TCPSession& operator=(const TCPSession& _other) = delete;
	TCPSession& operator=(const TCPSession&& _other) = delete;

private:
	static void OnCallback(PtrWTCPSession _weakSession, BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped);

	void SetReuse();
	bool BindQueue(const ServerQueue& _jobQueue);
	
	void RequestRecv();
	void OnRecv(const char* _data, DWORD _byteSize);

	void Close(bool _forceClose = false);
	void CloseSocket();
	void DisconnectSocket();
	void UnregisterSession();

private:
	// friend class 접근함수
	SOCKET GetSessionSocket() const;
	void Initialize();

public: // member Func
	__int64 GetSessionID() const;
	void SetCallBack(RecvCallBack _recvCallBack, CloseCallBack _closeCallBack);
};
