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
	std::vector<std::shared_ptr<ServerThread>>		m_vecThread;
	std::vector<std::shared_ptr<ServerIOCPWorker>>	m_vecIOCPWorker;

public: // default
	ServerIOCP(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount);
	~ServerIOCP();

	ServerIOCP(const ServerIOCP& _other) = delete;
	ServerIOCP(ServerIOCP&& _other) noexcept;

protected:
	ServerIOCP& operator=(const ServerIOCP& _other) = delete;
	ServerIOCP& operator=(const ServerIOCP&& _other) = delete;

private:
	void Initialize(std::function<void(std::shared_ptr<ServerIOCPWorker>)> func, UINT _threadCount);

public: // member Func
	void PostQueued(DWORD _dwNumberOfBytesTransferred, ULONG_PTR _dwCompletionKey);
};
