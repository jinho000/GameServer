#pragma once
#include "GameServerOverlapped.h"
#include <memory>

// 용도 :
// 분류 :
// 첨언 :
class UDPRecvOverlapped
	: public GameServerOverlapped
{
public:
	UDPRecvOverlapped(std::weak_ptr<class UDPSession> _UDPSession);
	UDPRecvOverlapped() = default;
	~UDPRecvOverlapped() {}

	void Execute(BOOL Result, DWORD _ByteSize) override;

	void* GetBuffer() {
		return Buffer;
	}

	inline LPDWORD GetBufferLength()
	{
		return &numberofBytes_;
	}

	inline LPWSABUF GetWSABuffer() {
		return &wsaBuffer;
	}

private:
	std::weak_ptr<class UDPSession> UDPSession_;
	// 절대로 겹치면 안됩니다.
	// 받은 데이터가 들어가야 하니까.
	char Buffer[1024];
	WSABUF wsaBuffer;
	DWORD numberofBytes_;
};