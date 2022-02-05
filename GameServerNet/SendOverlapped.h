#pragma once
#include "Overlapped.h"
// �뵵 :
// �з� :
// ÷�� :
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
	
	// ���ο� ���� ����
	void New(size_t _maxBufferLength);
	// �ܺο��� ������ ���۸� ����
	void CopyFrom(const std::vector<char>& _from);

	int GetMaxBufferLength();
	LPWSABUF GetBuffer();
};
