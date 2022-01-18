#include "pch.h"
#include "ServerQueue.h"
#include "ServerDebug.h"
#include "ServerDebug.h"

void ServerQueue::QueueFunction(std::shared_ptr<ServerIOCPWorker> _work, ServerQueue* _this, const std::string& _threadName)
{
	if (nullptr == _this)
	{
		ServerDebug::AssertDebugMsg("ť ������ ������ ����");
	}

	// ������ �̸� ����
	std::wstring String;
	String.assign(_threadName.begin(), _threadName.end());
	HRESULT hr = SetThreadDescription(GetCurrentThread(), String.c_str());

	// ������ �� ����
	BOOL result = _work->Wait(INFINITE);

	IocpWaitReturnType checkType = IocpWaitReturnType::RETURN_OK;
	if (0 == result)
	{
		if (WAIT_TIMEOUT == GetLastError())
		{
			checkType = IocpWaitReturnType::RETURN_TIMEOUT;
		}
		checkType = IocpWaitReturnType::RETURN_ERROR;
	}

	while (true)
	{
		switch (checkType)
		{
		case IocpWaitReturnType::RETURN_TIMEOUT:  break;
		case IocpWaitReturnType::RETURN_OK:
		{
			DWORD msgType = _work->GetNumberOfBytes();
			if (-1 == msgType)
			{
				return;
			}

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
		case IocpWaitReturnType::RETURN_ERROR: break;
		default:
			break;
		}
	}
	
}

ServerQueue::ServerQueue(WORK_TYPE _workType, UINT _threadCount, const std::string& _threadName)
	: ServerNameBase("serverQueue")
	, m_Iocp(std::bind(ServerQueue::QueueFunction, std::placeholders::_1, this, _threadName), _threadCount)
{
	
}

//ServerQueue::ServerQueue(ServerQueue&& _other) noexcept
//	: ServerNameBase(_other.GetName())
//{
//}

ServerQueue::~ServerQueue()
{
}

ServerQueue& ServerQueue::operator=(const ServerQueue&& _other)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}


void ServerQueue::Enqueue(const std::function<void()> _callback)
{
	std::unique_ptr<PostJob> postJob = std::make_unique<PostJob>();
	postJob->task = _callback;
	m_Iocp.PostQueued(0, reinterpret_cast<ULONG_PTR>(postJob.get()));
	postJob.release();
}

bool ServerQueue::NetworkAyncBind(SOCKET _socket, std::function<void(BOOL, DWORD, LPOVERLAPPED)> _callback)
{
	// socket�� completionkey�� ����Ǿ�����
	// �񵿱�� ��û�� �ö����� completionkey�� ���޵�
	// unique_ptr�� �� ��� ���޹޾� �����͸� �����ϹǷ� ������ ��
	std::unique_ptr<OverlappedJob> overJobPtr = std::make_unique<OverlappedJob>();
	overJobPtr->task = _callback;
	if (false == m_Iocp.AsyncBind(reinterpret_cast<HANDLE>(_socket), reinterpret_cast<ULONG_PTR>(overJobPtr.get())))
	{
		return false;
	}

	overJobPtr.release();

	return true;
}
