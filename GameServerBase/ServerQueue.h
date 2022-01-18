#pragma once
#include "ServerNameBase.h"
#include "ServerIOCPWorker.h"
#include "ServerIOCP.h"
// 용도 :
// 분류 :
// 첨언 : IOCP를 감싸 기본규칙을 정의한 큐
class ServerQueue : public ServerNameBase
{
private:
	static void QueueFunction(std::shared_ptr<ServerIOCPWorker> _work, ServerQueue* _this, const std::string& _threadName);

public: // type
	enum class WORK_TYPE : char
	{
		Default,	// 포스트큐 사용 타입
		Extension	// GetQueuedCompletionStatusEx로 여러개 사용 타입
	};

private: // data
	// 내가 일시키는 용 job
	struct PostJob : public std::enable_shared_from_this<PostJob>
	{
		std::function<void()> task;
	};

	// 비동기 입출력용 job
	struct OverlappedJob : public std::enable_shared_from_this<OverlappedJob>
	{
		std::function<void(BOOL, DWORD, LPOVERLAPPED)> task;
	};

private: // member var
	ServerIOCP m_Iocp;

public: // default
	ServerQueue() = delete;

	ServerQueue(WORK_TYPE _workType, UINT _threadCount, const std::string& _threadName = "thread queue");

	ServerQueue(const ServerQueue& _other) = delete;
	ServerQueue(ServerQueue&& _other) = delete;

	~ServerQueue();

protected:
	ServerQueue& operator=(const ServerQueue& _other) = delete;
	ServerQueue& operator=(const ServerQueue&& _other) = delete;

private:

public: // member Func
	void Enqueue(const std::function<void()> _callback);

	bool NetworkAyncBind(SOCKET _socket, std::function<void(BOOL, DWORD, LPOVERLAPPED)> _callback);
};

