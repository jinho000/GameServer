#pragma once
#include "ServerNameBase.h"
#include "ServerIOCPWorker.h"
#include "ServerIOCP.h"
// �뵵 :
// �з� :
// ÷�� : IOCP�� ���� �⺻��Ģ�� ������ ť
class ServerQueue : public ServerNameBase
{
private:
	static void QueueFunction(std::shared_ptr<ServerIOCPWorker> _work, ServerQueue* _this, const std::string& _threadName);

public: // type
	enum class WORK_TYPE : char
	{
		Default,	// ����Ʈť ��� Ÿ��
		Extension	// GetQueuedCompletionStatusEx�� ������ ��� Ÿ��
	};

private: // private type
	enum class WORK_MSG
	{
		POST_JOB = -2,
		WORK_DESTROY = -1,	
	};

private: // data
	// ���� �Ͻ�Ű�� �� job
	struct PostJob : public std::enable_shared_from_this<PostJob>
	{
		std::function<void()> task;
	};

	// �񵿱� ����¿� job
	struct OverlappedJob : public std::enable_shared_from_this<OverlappedJob>
	{
		std::function<void(BOOL, DWORD, LPOVERLAPPED)> task;
	};

private: // member var
	ServerIOCP m_Iocp;

public: // default
	ServerQueue();
	ServerQueue(WORK_TYPE _workType, UINT _threadCount, const std::string& _threadName = "thread queue");

	ServerQueue(const ServerQueue& _other) = delete;
	ServerQueue(ServerQueue&& _other) = delete;

	~ServerQueue();

protected:
	ServerQueue& operator=(const ServerQueue& _other) = delete;
	ServerQueue& operator=(const ServerQueue&& _other) = delete;

private:
	void Run(std::shared_ptr<ServerIOCPWorker> _Work);

public: // member Func
	void Enqueue(const std::function<void()> _callback);

	bool NetworkAyncBind(SOCKET _socket, std::function<void(BOOL, DWORD, LPOVERLAPPED)> _callback) const;

public: // thread local ���
	template<typename LocalDataType>
	void InitializeLocalData(WORK_TYPE _Type, int threadCount, const std::string& _ThreadName)
	{
		m_Iocp.InitializeLocalData<LocalDataType>(std::bind(ServerQueue::QueueFunctionLocalData<LocalDataType>, std::placeholders::_1, this, _ThreadName), INFINITE, threadCount);
	}

	template<typename LocalDataType>
	static void QueueFunctionLocalData(std::shared_ptr<ServerIOCPWorker> _Work, ServerQueue* _this, const std::string& _Name)
	{
		if (nullptr == _this)
		{
			ServerDebug::AssertDebugMsg("ť ������ ������ �����߽��ϴ�.");
		}

		ServerThread::SetThreadName(_Name + " " + std::to_string(_Work->GetIndex()));

		// thread local ������ ������ ����
		ServerThread::CreateThreadLocalData<LocalDataType>();

		_this->Run(_Work);
	}

};

