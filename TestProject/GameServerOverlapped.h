#pragma once

// �뵵 :
// �з� :
// ÷�� :
class GameServerOverlapped
{
public:
	GameServerOverlapped();
	virtual ~GameServerOverlapped() = 0 {};

public:
	LPWSAOVERLAPPED GetOverlapped();

protected:
	WSAOVERLAPPED Overlapped_;

public:
	void ResetOverlapped();

	virtual void Execute(BOOL Result, DWORD _ByteSize);

};
