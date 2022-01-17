#include "pch.h"
#include "ServerQueue.h"
#include "ServerDebug.h"
#include "ServerDebug.h"

void ServerQueue::QueueFunction(std::shared_ptr<ServerIOCPWorker> _work, ServerQueue* _this, const std::string& _threadName)
{
	if (nullptr == _this)
	{
		ServerDebug::AssertDebugMsg("큐 쓰레드 생성에 실패");
	}

	// 스레드 이름 설정
	std::wstring String;
	String.assign(_threadName.begin(), _threadName.end());
	HRESULT hr = SetThreadDescription(GetCurrentThread(), String.c_str());

	// 스레드 일 시작
	bool isFinish = false;
	while (!isFinish)
	{
		IocpWaitReturnType returnType = _work->Wait(1000);

		switch (returnType)
		{
		case IocpWaitReturnType::RETURN_TIMEOUT: isFinish = true; break;
		case IocpWaitReturnType::RETURN_OK:
		{
			DWORD msgType = _work->GetNumberOfBytes();
			if (-1 == msgType)
			{
				isFinish = true;
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
		case IocpWaitReturnType::RETURN_ERROR: isFinish = true; break;
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


void ServerQueue::Enqueue(const std::function<void()> _callback)
{
	std::unique_ptr<PostJob> postJob = std::make_unique<PostJob>();
	postJob->task = _callback;
	m_Iocp.PostQueued(0, reinterpret_cast<ULONG_PTR>(postJob.get()));
	postJob.release();
}