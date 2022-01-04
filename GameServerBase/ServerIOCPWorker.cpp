#include "pch.h"
#include "ServerIOCPWorker.h"
#include "ServerDebug.h"

ServerIOCPWorker::ServerIOCPWorker(HANDLE _IOCPHandle, DWORD _timeout)
	: m_IOCPHandle(_IOCPHandle)
	, m_lpNumberOfBytesTransferred(0)
	, m_lpCompletionKey(0)
	, m_lpOverlapped(nullptr)
	, m_dwMilliseconds(_timeout)

{
}

ServerIOCPWorker::~ServerIOCPWorker()
{
}

ServerIOCPWorker::ServerIOCPWorker(ServerIOCPWorker&& _other) noexcept
	: m_IOCPHandle(_other.m_IOCPHandle)
	, m_lpNumberOfBytesTransferred(_other.m_lpNumberOfBytesTransferred)
	, m_lpCompletionKey(_other.m_lpCompletionKey)
	, m_lpOverlapped(_other.m_lpOverlapped)
	, m_dwMilliseconds(_other.m_dwMilliseconds)
{
}

IocpWaitReturnType ServerIOCPWorker::Wait()
{
	BOOL LastWaitValue = GetQueuedCompletionStatus(m_IOCPHandle, &m_lpNumberOfBytesTransferred, &m_lpCompletionKey, &m_lpOverlapped, INFINITE);

	switch (LastWaitValue)
	{
	case 0: return IocpWaitReturnType::RETURN_TIMEOUT;
	case 1: return IocpWaitReturnType::RETURN_POST;
	default:
		break;
	}

	ServerDebug::AssertDebug();
	return IocpWaitReturnType::RETURN_ERROR;
}


