#pragma once
#include "Overlapped.h"

// 용도 :
// 분류 :
// 첨언 :
class RecvOverlapped : public Overlapped
{
private: // member var
	char		m_Buffer[1024]; // 전달받을 데이터
	WSABUF		m_wsaBuffer;
	TCPSession* m_tcpSession;

public: // default
	RecvOverlapped(TCPSession* _tcpSession);
	~RecvOverlapped();

	RecvOverlapped(const RecvOverlapped& _other) = delete;
	RecvOverlapped(RecvOverlapped&& _other) = delete;

protected:
	RecvOverlapped& operator=(const RecvOverlapped& _other) = delete;
	RecvOverlapped& operator=(const RecvOverlapped&& _other) = delete;

private:

public: // member Func
	void Clear();
	void Excute(BOOL Result, DWORD _ByteSize) override;
	void* GetBuffer();
	LPWSABUF GetWSABuffer();
	PtrSTCPSession GetTCPSession();
};

