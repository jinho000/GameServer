#pragma once
#include "Overlapped.h"
//#include "TCPSession.h"
// 용도 :
// 분류 :
// 첨언 :
class DisconnectOverlapped : public Overlapped
{
private: // member var
	PtrSTCPSession m_tcpSession;

public: // default
	DisconnectOverlapped(PtrSTCPSession _tcpSession);
	~DisconnectOverlapped();

	DisconnectOverlapped(const DisconnectOverlapped& _other) = delete;
	DisconnectOverlapped(DisconnectOverlapped&& _other) noexcept;

protected:
	DisconnectOverlapped& operator=(const DisconnectOverlapped& _other) = delete;
	DisconnectOverlapped& operator=(const DisconnectOverlapped&& _other) = delete;

private:

public: // member Func
	void Excute(BOOL _result, DWORD _byteSize) override;
};

