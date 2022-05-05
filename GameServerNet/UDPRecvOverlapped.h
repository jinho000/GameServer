#pragma once
#include "Overlapped.h"

class UDPSession;
class UDPRecvOverlapped : public Overlapped
{
private: // member var
	char		m_buffer[1024]; // 전달받을 데이터
	WSABUF		m_wsaBuffer;
	DWORD		m_numberofBytes;
	//std::weak_ptr<class UDPSession> UDPSession_;
	UDPSession* m_udpSession;

public: // default
	UDPRecvOverlapped(UDPSession* _udpSession);
	~UDPRecvOverlapped();

	UDPRecvOverlapped(const UDPRecvOverlapped& _other) = delete;
	UDPRecvOverlapped(UDPRecvOverlapped&& _other) = delete;
	UDPRecvOverlapped& operator=(const UDPRecvOverlapped& _other) = delete;
	UDPRecvOverlapped& operator=(const UDPRecvOverlapped&& _other) = delete;

public: // member Func
	void Clear();
	void Excute(BOOL Result, DWORD _ByteSize) override;
	void* GetBuffer();
	LPWSABUF GetWSABuffer();
	LPDWORD GetBufferLength();
};

