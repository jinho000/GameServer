#pragma once

// 용도 :
// 분류 :
// 첨언 :
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
