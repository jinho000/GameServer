#include "pch.h"
#include "ServerIOCP.h"
#include "ServerDebug.h"


ServerIOCP::ServerIOCP()
	: m_IOCPHandle(NULL)
{
}

ServerIOCP::ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount)
	: m_IOCPHandle(NULL)
{
	Initialize(func, _threadCount);
}

ServerIOCP::~ServerIOCP()
{	
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
	if (NULL != m_IOCPHandle)
	{
		ServerDebug::LogWarning("Handle is not NULL");
		return;
	}

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
		return;
	}

	m_vecThread.reserve(threadCount);
	m_vecIOCPWorker.reserve(threadCount);

	for (UINT i = 0; i < threadCount; ++i)
	{
		m_iocpLock.lock();

		std::shared_ptr<ServerIOCPWorker> iocpWorker = std::make_shared<ServerIOCPWorker>(m_IOCPHandle, (UINT)m_vecIOCPWorker.size());
		m_vecIOCPWorker.push_back(iocpWorker);

		std::shared_ptr<ServerThread> NewThread = std::make_shared<ServerThread>(func, iocpWorker);
		NewThread->SetThreadOrder(i);
		m_vecThread.push_back(NewThread);

		m_iocpLock.unlock();
	}
}

size_t ServerIOCP::GetThreadCount() const
{
	return m_vecThread.size();
}

void ServerIOCP::PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey) const
{
	if (nullptr == m_IOCPHandle)
	{
		ServerDebug::AssertDebug();
	}

	PostQueuedCompletionStatus(m_IOCPHandle, _dwNumberOfBytesTransferred, _dwCompletionKey, nullptr);
}

bool ServerIOCP::BindHandle(HANDLE _handle, ULONG_PTR _dwCompletionKey) const
{
	if (nullptr == m_IOCPHandle)
	{
		return false;
	}

	if (m_IOCPHandle != CreateIoCompletionPort(_handle, m_IOCPHandle, _dwCompletionKey, 0))
	{
		return false;
	}

	return true;
}

void ServerIOCP::InitHandle(UINT _count)
{
	m_IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, /*스레드 개수*/ _count);
}

BOOL ServerIOCP::Execute(DWORD& NumberOfBytesTransferred, ULONG_PTR& CompletionKey, LPOVERLAPPED& lpOverlapped, DWORD _Time)
{
	return GetQueuedCompletionStatus(m_IOCPHandle, &NumberOfBytesTransferred, &CompletionKey, &lpOverlapped, _Time);
}