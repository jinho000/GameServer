#pragma once
#include "ServerBaseObject.h"

class ServerIOCPWorker : public ServerBaseObject
{
private: // member var
	HANDLE			m_IOCPHandle;
	DWORD			m_lpNumberOfBytesTransferred;
	ULONG_PTR		m_lpCompletionKey;
	LPOVERLAPPED	m_lpOverlapped;
	UINT			m_index;

public: // default
	ServerIOCPWorker(HANDLE _IOCPHandle, UINT _index);
	~ServerIOCPWorker();

	ServerIOCPWorker(const ServerIOCPWorker& _other) = delete;
	ServerIOCPWorker(ServerIOCPWorker&& _other) = delete;

protected:
	ServerIOCPWorker& operator=(const ServerIOCPWorker& _other) = delete;
	ServerIOCPWorker& operator=(const ServerIOCPWorker&& _other) = delete;

private:

public: // member Func
	BOOL Wait(DWORD _timeoutMillSecond);

	DWORD GetNumberOfBytes()
	{
		return m_lpNumberOfBytesTransferred;
	}

	ULONG_PTR GetCompletionKey()
	{
		return m_lpCompletionKey;
	}

	template<typename type>
	type GetCompletionKeyType()
	{
		return reinterpret_cast<type>(m_lpCompletionKey);
	}

	LPOVERLAPPED GetOverlappedPtr()
	{
		return m_lpOverlapped;
	}

	UINT GetIndex()
	{
		return m_index;
	}
};

