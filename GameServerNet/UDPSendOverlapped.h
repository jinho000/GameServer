#pragma once
#include "Overlapped.h"

// 용도 :
// 분류 :
// 첨언 :
class UDPSendOverlapped : public Overlapped
{
private: // member var
	char				m_buffer[1024];
	WSABUF				m_wsaBuff;
	DWORD				m_numberofBytes;
	UDPSession*			m_udpSession;

public: // default
	UDPSendOverlapped(UDPSession* _udpSession);
	~UDPSendOverlapped();

	UDPSendOverlapped(const UDPSendOverlapped& _other) = delete;
	UDPSendOverlapped(UDPSendOverlapped&& _other) = delete;
	UDPSendOverlapped& operator=(const UDPSendOverlapped& _other) = delete;
	UDPSendOverlapped& operator=(const UDPSendOverlapped&& _other) = delete;

public: // member Func
	void Clear();
	void Excute(BOOL _result, DWORD _byteSize) override;
	void CopyFrom(const std::vector<uint8_t>& _from); // 외부에서 전달한 버퍼를 복사

	LPDWORD GetBufferLength();
	LPWSABUF GetBuffer(); 
};

