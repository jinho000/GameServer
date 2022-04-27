#include "pch.h"
#include "ServerIOCPWorker.h"
#include "ServerDebug.h"

ServerIOCPWorker::ServerIOCPWorker(HANDLE _IOCPHandle, UINT _index)
	: m_IOCPHandle(_IOCPHandle)
	, m_lpNumberOfBytesTransferred(0)
	, m_lpCompletionKey(0)
	, m_lpOverlapped(nullptr)
	, m_index(_index)

{
}

ServerIOCPWorker::~ServerIOCPWorker()
{
}

//ServerIOCPWorker::ServerIOCPWorker(ServerIOCPWorker&& _other) noexcept
//	: m_IOCPHandle(_other.m_IOCPHandle)
//	, m_lpNumberOfBytesTransferred(_other.m_lpNumberOfBytesTransferred)
//	, m_lpCompletionKey(_other.m_lpCompletionKey)
//	, m_lpOverlapped(_other.m_lpOverlapped)
//	, m_index(_other.m_index)
//{
//}

BOOL ServerIOCPWorker::Wait(DWORD _timeoutMillSecond)
{
	return GetQueuedCompletionStatus(m_IOCPHandle
		, &m_lpNumberOfBytesTransferred
		, &m_lpCompletionKey
		, &m_lpOverlapped
		, _timeoutMillSecond
	);
}


