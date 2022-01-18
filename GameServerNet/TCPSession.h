#pragma once
#include "IPEndPoint.h"

// �뵵 : ������ Ŭ���� ����
// �з� :
// ÷�� : 
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
	// friend class �����Լ�
	SOCKET GetSessionSocket() const;

public: // member Func
	__int64 GetSessionID() const;
};

