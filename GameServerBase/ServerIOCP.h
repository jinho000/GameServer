#pragma once
#include "ServerThread.h"
#include "ServerBaseObject.h"
#include "ServerIOCPWorker.h"

// 용도 : 스레드 관리 클래스
// 분류 :
// 첨언 :
class ServerIOCP : public ServerBaseObject
{
private: // member var
	HANDLE											m_IOCPHandle;
	std::mutex										m_iocpLock;
	std::vector<std::shared_ptr<ServerThread>>		m_vecThread;
	std::vector<std::shared_ptr<ServerIOCPWorker>>	m_vecIOCPWorker;

public: // default
	ServerIOCP();
	ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount);
	~ServerIOCP();

	ServerIOCP(const ServerIOCP& _other) = delete;
	ServerIOCP(ServerIOCP&& _other) noexcept;

protected:
	ServerIOCP& operator=(const ServerIOCP& _other) = delete;
	ServerIOCP& operator=(const ServerIOCP&& _other) = delete;

private:

public: // member Func
	void Initialize(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount);
	size_t GetThreadCount() const;

	void PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey) const;
	bool BindHandle(HANDLE _handle, ULONG_PTR _dwCompletionKey) const;

public:
	// post work를 위한 IOCP
	void InitHandle(UINT _count);
	BOOL Execute(DWORD& NumberOfBytesTransferred, ULONG_PTR& CompletionKey, LPOVERLAPPED& lpOverlapped, DWORD _Time);


public: // thread local 사용
	template<typename LocalDataType>
	void InitializeLocalData(std::function<void(std::shared_ptr<ServerIOCPWorker>)> _Func, DWORD _Time, int _threadCount)
	{
		if (NULL != m_IOCPHandle)
		{
			ServerDebug::LogWarning("Handle is not NULL");
			return;
		}

		UINT threadCount = _threadCount;
		if (threadCount <= 0)
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
			std::shared_ptr<ServerIOCPWorker> iocpWorker = std::make_shared<ServerIOCPWorker>(m_IOCPHandle, (UINT)m_vecIOCPWorker.size());
			m_vecIOCPWorker.push_back(iocpWorker);

			std::shared_ptr<ServerThread> NewThread = std::make_shared<ServerThread>(_Func, iocpWorker);
			NewThread->SetThreadOrder(i);
			m_vecThread.push_back(NewThread);

			m_iocpLock.unlock();
		}
	}

};
