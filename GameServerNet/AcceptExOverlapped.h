#pragma once
#include "Overlapped.h"
// 용도 : AcceptEx에서 사용하는 Overlapped 데이터
// 분류 :
// 첨언 :
class AcceptExOverlapped : public Overlapped
{
private: // member var
	char		m_buffer[128]; // local, remote 주소값을 저장하기위해 사용
	TCPSession* m_tcpSession;


public: // default
	AcceptExOverlapped(TCPSession* _tcpSession);
	~AcceptExOverlapped() = default;

	AcceptExOverlapped(const AcceptExOverlapped& _other) = delete;
	AcceptExOverlapped(AcceptExOverlapped&& _other) = delete;
	AcceptExOverlapped& operator=(const AcceptExOverlapped& _other) = delete;
	AcceptExOverlapped& operator=(const AcceptExOverlapped&& _other) = delete;

private:

public: // member Func
	void Excute(BOOL _result, DWORD _byteSize);
	void* GetBuffer();
	PtrSTCPSession GetTCPSession();

};

