#pragma once
#include "ServerBaseObject.h"

enum class IocpWaitReturnType
{
	RETURN_TIMEOUT,
	RETURN_POST,
	RETURN_ERROR
};

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
	ServerIOCPWorker(ServerIOCPWorker&& _other) noexcept;

protected:
	ServerIOCPWorker& operator=(const ServerIOCPWorker& _other) = delete;
	ServerIOCPWorker& operator=(const ServerIOCPWorker&& _other) = delete;

private:

public: // member Func
	IocpWaitReturnType Wait(DWORD _timeoutMillSecond);

	DWORD GetNumberOfBytes()
	{
		return m_lpNumberOfBytesTransferred;
	}

	template<typename type>
	type GetCompletionKey()
	{
		return reinterpret_cast<type>(m_lpCompletionKey);
	}

	UINT GetIndex()
	{
		return m_index;
	}
};

