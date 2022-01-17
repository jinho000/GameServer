#include "pch.h"
#include "ServerIOCP.h"
#include "ServerDebug.h"


ServerIOCP::ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount)
	: m_IOCPHandle(NULL)
{
	Initialize(func, _threadCount);
}

ServerIOCP::~ServerIOCP()
{
	for (int i = 0; i < m_vecThread.size(); ++i)
	{
		PostQueued(-1, 0);
		Sleep(1);
	}
	
	for (int i = 0; i < m_vecThread.size(); ++i)
	{
		m_vecThread[i]->Join();
	}
}

ServerIOCP::ServerIOCP(ServerIOCP&& _other) noexcept
	: m_IOCPHandle(_other.m_IOCPHandle)
{
}

void ServerIOCP::Initialize(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount)
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
	m_vecIOCPWorker.reserve(threadCount);

	for (UINT i = 0; i < threadCount; ++i)
	{
		m_iocpLock.lock();
		std::shared_ptr<ServerIOCPWorker> iocpWorker = std::make_shared<ServerIOCPWorker>(m_IOCPHandle, m_vecIOCPWorker.size());
		m_vecIOCPWorker.push_back(iocpWorker);
		m_vecThread.push_back(std::make_shared<ServerThread>(func, iocpWorker));
		m_iocpLock.unlock();
	}
}

size_t ServerIOCP::GetThreadCount()
{
	return m_vecThread.size();
}

void ServerIOCP::PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey)
{
	PostQueuedCompletionStatus(m_IOCPHandle, _dwNumberOfBytesTransferred, _dwCompletionKey, nullptr);
}
