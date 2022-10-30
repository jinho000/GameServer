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
class TCPSession : public ServerBaseObject
{
private:
	// friend class
	friend class TCPListener;
	friend class RecvOverlapped;
	friend class AcceptExOverlapped;
	friend class SendOverlapped;

private: // member var
	__int64		m_conectId;
	SOCKET		m_sessionSocket;
	IPEndPoint	m_localAddr;
	IPEndPoint	m_remoteAddr;

	// overlapped
	AcceptExOverlapped*		m_acceptExOverlapped;
	RecvOverlapped*			m_recvOverlapped;

	// send를 동시에 여러개 보낼수 있어야함 (Sendpool)
	SendOverlapped*			m_sendOverlapped;

	// callback
	using IOCallback = std::function<void(BOOL, DWORD, LPOVERLAPPED)>;
	IOCallback				m_IOCallback; // 세션소켓 IO이벤트 발생시 호출함수 함수객체

	using RecvCallBack = std::function<void(PtrSTCPSession, const std::vector<uint8_t>&)>;
	RecvCallBack			m_recvCallBack; // 클라이언트의 리시브 데이터 처리함수

	using CloseCallBack = std::function<void(PtrSTCPSession)>;
	CloseCallBack			m_closeCallBack;

	//ServerObjectPool<SendOverlapped> m_sendPool;

	// 리시브로 받은 데이터를 처리하기위한 버퍼
	// TCP의 경우 데이터의 경계가 없기 때문에 패킷의 전체데이터를 확인 후 처리해야한다
	// 패킷 크기의 단위는 byte로 처리
	std::vector<uint8_t>	m_recvBuffer;
	UINT					m_packetSize;

public: // default
	TCPSession();
	~TCPSession();

	TCPSession(const TCPSession& _other) = delete;
	TCPSession(TCPSession&& _other) = delete;
	TCPSession& operator=(const TCPSession& _other) = delete;
	TCPSession& operator=(const TCPSession&& _other) = delete;

private:
	// friend class 접근
	void Initialize();
	AcceptExOverlapped* GetAcceptExOverlapped() { return m_acceptExOverlapped; }

private:
	// 세션소켓에 IO이벤트 발생시 호출함수
	void OnCallback(BOOL _result, DWORD _numberOfBytes, LPOVERLAPPED _lpOverlapped);

	// workQueue에 세션소켓 연결(등록)
	bool BindQueue(const ServerQueue& _workQueue);
	
	void RequestRecv();
	void OnRecv(const char* _data, DWORD _byteSize);

	void CloseSession();
	void CloseSocket();
	void UnregisterSession();

public: // member Func
	SOCKET GetSessionSocket() const;
	__int64 GetSessionID() const { return m_conectId; };
	void SetCallBack(RecvCallBack _recvCallBack, CloseCallBack _closeCallBack);
	void Send(const std::vector<uint8_t>& _buffer);

	TCPListener* GetTCPListener() { return GetParent<TCPListener>(); }
	const IPEndPoint& GetRemoteIPEndPoint() { return m_remoteAddr; }
};
