#pragma once
#include "ServerThread.h"
#include "ServerBaseObject.h"
#include "ServerThread.h"
#include "ServerIOCPWorker.h"

// 용도 :
// 분류 :
// 첨언 :
class ServerIOCP : public ServerBaseObject
{
private: // member var
	HANDLE											m_IOCPHandle;
	std::vector<std::shared_ptr<ServerThread>>		m_vecThread;
	std::vector<std::shared_ptr<ServerIOCPWorker>>	m_vecIOCPWorker;

public: // default
	ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount, UINT _timeout);
	~ServerIOCP();

	ServerIOCP(const ServerIOCP& _other) = delete;
	ServerIOCP(ServerIOCP&& _other) noexcept;

protected:
	ServerIOCP& operator=(const ServerIOCP& _other) = delete;
	ServerIOCP& operator=(const ServerIOCP&& _other) = delete;

private:

public: // member Func
	void PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey);
	
};
