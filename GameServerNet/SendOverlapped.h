#pragma once
#include "Overlapped.h"
// 용도 :
// 분류 :
// 첨언 :
class SendOverlapped : public Overlapped
{
private: // member var
	std::vector<char>	m_buffer;
	WSABUF				m_wsaBuff;
	TCPSession*			m_tcpSession;

public: // default
	SendOverlapped(TCPSession* _tcpSession);
	~SendOverlapped();

	SendOverlapped(const SendOverlapped& _other) = delete;
	SendOverlapped(SendOverlapped&& _other) = delete;
	SendOverlapped& operator=(const SendOverlapped& _other) = delete;
	SendOverlapped& operator=(const SendOverlapped&& _other) = delete;

private:
	void New(size_t _maxBufferLength); // 새로운 버퍼 생성

public: // member Func
	void Clear();
	void Excute(BOOL _result, DWORD _byteSize) override;
	void CopyFrom(const std::vector<uint8_t>& _from); // 외부에서 전달한 버퍼를 복사

	int GetMaxBufferLength();
	LPWSABUF GetBuffer();
};

