#include "pch.h"
#include "ServerIOCP.h"
#include "ServerDebug.h"

ServerIOCP::ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount, UINT _timeout)
{
	UINT threadCount = _threadCount;
	if (0 == _threadCount)
	{
		SYSTEM_INFO Sys;
		GetSystemInfo(&Sys);
		threadCount = Sys.dwNumberOfProcessors;
	}

	m_IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, /*스레드 개수*/ threadCount);

	if (nullptr == m_IOCPHandle)
	{
		ServerDebug::AssertDebug();
	}

	m_vecThread.reserve(threadCount);
	for (UINT i = 0; i < threadCount; ++i)
	{
		std::shared_ptr<ServerIOCPWorker> iocpWorker = std::make_shared<ServerIOCPWorker>(m_IOCPHandle, _timeout);
		m_vecThread.push_back(std::make_shared<ServerThread>(func, iocpWorker));
		m_vecIOCPWorker.push_back(iocpWorker);
	}
}

ServerIOCP::~ServerIOCP()
{
	// thread.join?
}

ServerIOCP::ServerIOCP(ServerIOCP&& _other) noexcept
	: m_IOCPHandle(_other.m_IOCPHandle)
{
}

void ServerIOCP::PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey)
{
	PostQueuedCompletionStatus(m_IOCPHandle, _dwNumberOfBytesTransferred, _dwCompletionKey, nullptr);
}
