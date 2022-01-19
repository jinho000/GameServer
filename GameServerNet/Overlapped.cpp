#include "pch.h"
#include "Overlapped.h"

LPWSAOVERLAPPED Overlapped::GetLPOverlapped()
{
    return &m_overlapped;
}

void Overlapped::ResetOverlapped()
{
    memset(&m_overlapped, 0, sizeof(WSAOVERLAPPED));
}
