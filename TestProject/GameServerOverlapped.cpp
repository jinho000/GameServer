#include "pch.h"
#include "GameServerOverlapped.h"

GameServerOverlapped::GameServerOverlapped()
	: Overlapped_()
{
	ResetOverlapped();
}

void GameServerOverlapped::ResetOverlapped()
{
	memset(&Overlapped_, 0x00, sizeof(WSAOVERLAPPED));
}

LPWSAOVERLAPPED GameServerOverlapped::GetOverlapped()
{
	return &Overlapped_;
}

void GameServerOverlapped::Execute(BOOL Result, DWORD _ByteSize)
{

}
