#pragma once
#include "IPEndPoint.h"
#include "GameServerBase/ServerBaseObject.h"
#include "GameServerBase/ServerQueue.h"
#include "GameServerBase/ServerObjectPool.h"
#include "SendOverlapped.h"
#include "AcceptExOverlapped.h"
#include "TCPListener.h"

// 클라이언트와 연결할 세션
class RecvOverlapped;
class AcceptExOverlapped;
class DisconnectOverlapped;
class TCPSession : public ServerBaseObject
{
private:
	// friend class
	friend class TCPListener;
	friend class RecvOverlapped;
	friend class DisconnectOverlapped;
	friend class SendOverlapped;

private: // member var
	__int64		m_conectId;
	SOCKET		m_sessionSocket;
	IPEndPoint	m_localAddr;
	IPEndPoint	m_remoteAddr;

	// overlapped
	AcceptExOverlapped*		m_acceptExOverlapped;
	RecvOverlapped*			m_recvOverlapped;
	DisconnectOverlapped*	m_disconOverlapped;

	// callback
	using RecvCallBack = std::function<void(PtrSTCPSession, const std::vector<uint8_t>&)>;
	RecvCallBack			m_recvCallBack;

	using CloseCallBack = std::function<void(PtrSTCPSession)>;
	CloseCallBack			m_closeCallBack;

	ServerObjectPool<SendOverlapped> m_sendPool;

	std::atomic_bool		m_callClose;
	std::atomic_bool		m_bReuseSocket;

public: // default
	TCPSession();
	~TCPSession();

	TCPSession(const TCPSession& _other) = delete;
	TCPSession(TCPSession&& _other) = delete;
	TCPSession& operator=(const TCPSession& _other) = delete;
	TCPSession& operator=(const TCPSession&& _other) = delete;

private:
	// friend class 접근함수
	void Initialize();
	SOCKET GetSessionSocket() const;
	AcceptExOverlapped* GetAcceptExOverlapped() { return m_acceptExOverlapped; }

private:
	static void OnCallback(PtrWTCPSession _weakSession, BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped);

	void SetReuse();
	bool BindQueue(const ServerQueue& _jobQueue);
	
	void RequestRecv();
	void OnRecv(const char* _data, DWORD _byteSize);

	void OnSendComplete(SendOverlapped* _sendOverlapped);

	void Close(bool _forceClose = false);
	void CloseSocket();
	void DisconnectSocket();
	void UnregisterSession();

public: // member Func
	__int64 GetSessionID() const { return m_conectId; };
	void SetCallBack(RecvCallBack _recvCallBack, CloseCallBack _closeCallBack);
	void Send(const std::vector<uint8_t>& _buffer);

	TCPListener* GetTCPListener() { return GetParent<TCPListener>(); }
};
