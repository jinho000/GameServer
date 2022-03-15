#include "pch.h"
#include "ServerQueue.h"
#include "ServerDebug.h"

void ServerQueue::QueueFunction(std::shared_ptr<ServerIOCPWorker> _work, ServerQueue* _this, const std::string& _threadName)
{
	if (nullptr == _this)
	{
		ServerDebug::AssertDebugMsg("ť ������ ������ ����");
	}

	// ������ �̸� ����
	ServerThread::SetThreadName(_threadName + " " + std::to_string(_work->GetIndex()));

	// thread �۾� ����
	_this->Run(_work);
}

ServerQueue::ServerQueue()
	: ServerNameBase("serverQueue")
	, m_Iocp()
{
}

ServerQueue::ServerQueue(WORK_TYPE _workType, UINT _threadCount, const std::string& _threadName)
	: ServerNameBase("serverQueue")
	, m_Iocp(std::bind(ServerQueue::QueueFunction, std::placeholders::_1, this, _threadName), _threadCount)
{
	
}


ServerQueue::~ServerQueue()
{
}

void ServerQueue::Run(std::shared_ptr<ServerIOCPWorker> _work)
{
	while (true)
	{
		// ������ ���
		BOOL waitResult = _work->Wait(INFINITE);

		// ������ �� ����
		IocpWaitReturnType checkType = IocpWaitReturnType::RETURN_OK;
		if (0 == waitResult)
		{
			if (WAIT_TIMEOUT == GetLastError())
			{
				checkType = IocpWaitReturnType::RETURN_TIMEOUT;
				ServerDebug::LogInfo("work wait return timeout");
			}
			else
			{
				checkType = IocpWaitReturnType::RETURN_ERROR;
				ServerDebug::LogInfo("work wait return 0");
			}
		}


		DWORD MsgType = _work->GetNumberOfBytes();

		switch (MsgType)
		{
		case (DWORD)ServerQueue::WORK_MSG::WORK_DESTROY: break;
		case (DWORD)ServerQueue::WORK_MSG::POST_JOB:
		{
			std::unique_ptr<PostJob> jobTesk = std::unique_ptr<PostJob>(_work->GetCompletionKey<PostJob*>());
			if (nullptr != jobTesk)
			{
				jobTesk->task();
			}
			else
			{
				ServerDebug::LogError("PostJob Is Null");
			}
			break;
		}
		default: // post job�� �ƴ� �񵿱� ��� �۾��� ���
		{
			OverlappedJob* jobTesk = _work->GetCompletionKey<OverlappedJob*>();
			if (nullptr != jobTesk)
			{
				// �̰͵� ó���ؾ� �մϴ�.
				jobTesk->task(waitResult, _work->GetNumberOfBytes(), _work->GetOverlappedPtr());
			}
			else
			{
				ServerDebug::LogError("OverJob Is Null");
			}

			break;
		}
		}
	}
}

void ServerQueue::Enqueue(const std::function<void()> _callback)
{
	std::unique_ptr<PostJob> postJob = std::make_unique<PostJob>();
	postJob->task = _callback;
	m_Iocp.PostQueued((DWORD)WORK_MSG::POST_JOB, reinterpret_cast<ULONG_PTR>(postJob.get()));
	postJob.release();
}

bool ServerQueue::NetworkAyncBind(SOCKET _socket, std::function<void(BOOL, DWORD, LPOVERLAPPED)> _callback) const
{
	// socket�� completionkey�� ����Ǿ�����
	// �񵿱�� ��û�� �ö����� completionkey�� ���޵�
	// unique_ptr�� �� ��� ���޹޾� �����͸� �����ϹǷ� ������ ��
	std::unique_ptr<OverlappedJob> overJobPtr = std::make_unique<OverlappedJob>();
	overJobPtr->task = _callback;
	if (false == m_Iocp.AsyncBind(reinterpret_cast<HANDLE>(_socket), reinterpret_cast<ULONG_PTR>(overJobPtr.get())))
	{
		ServerDebug::GetLastErrorPrint();
		return false;
	}

	overJobPtr.release();

	return true;
}
