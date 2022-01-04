#pragma once
#include "ServerBaseObject.h"

// 용도 : iocp worker에 필요한 
// 분류 :
// 첨언 :

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
	DWORD			m_dwMilliseconds;

public: // default
	ServerIOCPWorker(HANDLE _IOCPHandle, DWORD _timeout);
	~ServerIOCPWorker();

	ServerIOCPWorker(const ServerIOCPWorker& _other) = delete;
	ServerIOCPWorker(ServerIOCPWorker&& _other) noexcept;

protected:
	ServerIOCPWorker& operator=(const ServerIOCPWorker& _other) = delete;
	ServerIOCPWorker& operator=(const ServerIOCPWorker&& _other) = delete;

private:

public: // member Func
	IocpWaitReturnType Wait();

	template<typename type>
	type GetCompletionKey()
	{
		return reinterpret_cast<type>(m_lpCompletionKey);
	}
};

