#pragma once
#include "GameServerOverlapped.h"
#include <memory>

// �뵵 :
// �з� :
// ÷�� :
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
	// ����� ��ġ�� �ȵ˴ϴ�.
	// ���� �����Ͱ� ���� �ϴϱ�.
	char Buffer[1024];
	WSABUF wsaBuffer;
	DWORD numberofBytes_;
};