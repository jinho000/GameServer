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
	PtrSTCPSession		m_tcpSession;

public: // default
	SendOverlapped();
	~SendOverlapped();

	SendOverlapped(const SendOverlapped& _other) = delete;
	SendOverlapped(SendOverlapped&& _other) = delete;

protected:
	SendOverlapped& operator=(const SendOverlapped& _other) = delete;
	SendOverlapped& operator=(const SendOverlapped&& _other) = delete;

private:

public: // member Func
	void SetTCPSession(PtrSTCPSession _tcpSession);

	void Excute(BOOL _result, DWORD _byteSize) override;
	
	// 새로운 버퍼 생성
	void New(size_t _maxBufferLength);
	// 외부에서 전달한 버퍼를 복사
	void CopyFrom(const std::vector<char>& _from);

	int GetMaxBufferLength();
	LPWSABUF GetBuffer();
};

