#pragma once
#include "IPEndPoint.h"

// 용도 : 서버와 클라의 연결
// 분류 :
// 첨언 : 
class TCPSession
{
private:
	// friend class
	friend class TCPListener;

private: // member var
	__int64		m_conectId;
	SOCKET		m_sessionSocket;
	//IPEndPoint	m_localAddr;
	//IPEndPoint	m_remoteAddr;

public: // default
	TCPSession();
	~TCPSession();

	TCPSession(const TCPSession& _other) = delete;
	TCPSession(TCPSession&& _other) noexcept;

protected:
	TCPSession& operator=(const TCPSession& _other) = delete;
	TCPSession& operator=(const TCPSession&& _other) = delete;

private:
	bool Initialize();

private:
	// friend class 접근함수
	SOCKET GetSessionSocket() const;

public: // member Func
	__int64 GetSessionID() const;
};

