#include "pch.h"
#include "ServerQueue.h"
#include "ServerDebug.h"

void ServerQueue::WorkThread(std::shared_ptr<ServerIOCPWorker> _work, const std::string& _threadName)
{
	// 스레드 이름 설정
	ServerThread::SetThreadName(_threadName + " " + std::to_string(_work->GetIndex()));

	// thread 작업 실행
	this->RunThread(_work);
}

ServerQueue::ServerQueue()
	: ServerNameBase("serverQueue")
	, m_Iocp()
{
}

ServerQueue::~ServerQueue()
{
}

void ServerQueue::RunThread(std::shared_ptr<ServerIOCPWorker> _worker)
{
	while (true)
	{
		// 스레드 대기
		BOOL waitResult = _worker->Wait(INFINITE);

		// 스레드 일 시작
		if (FALSE == waitResult)
		{
			if (WAIT_TIMEOUT == GetLastError())
			{
				ServerDebug::AssertDebugMsg("work wait return timeout");
				return;
			}
		}

		bool isExit = false;
		DWORD MsgType = _worker->GetNumberOfBytes();

		switch (MsgType)
		{
		case (DWORD)ServerQueue::WORK_MSG::WORK_DESTROY:
		{
			isExit = true;
			break;
		}
		case (DWORD)ServerQueue::WORK_MSG::PostWork:
		{
			if (0 != _worker->GetCompletionKey())
			{
				std::unique_ptr<PostWork> postJob 
					= std::unique_ptr<PostWork>(_worker->GetCompletionKeyType<PostWork*>());
				postJob->work();
			}
			else
			{
				ServerDebug::AssertDebugMsg("PostWork Is Null");
			}
			break;
		}
		default: // post job이 아닌 비동기 통신 작업일 경우
		{
			if (0 != _worker->GetCompletionKey())
			{
				std::function<void(BOOL, DWORD, LPOVERLAPPED)>* pJob 
					= _worker->GetCompletionKeyType<std::function<void(BOOL, DWORD, LPOVERLAPPED)>*>();
				(*pJob)(waitResult, _worker->GetNumberOfBytes(), _worker->GetOverlappedPtr());
			}
			else
			{
				ServerDebug::AssertDebugMsg("IOCallbackWork Is Null");
			}
			break;
		}
		}

		if (isExit)
		{
			break;
		}
	}
}

void ServerQueue::Enqueue(const std::function<void()>& _work)
{
	if (nullptr == _work)
	{
		ServerDebug::AssertDebugMsg("work is nullptr");
		return;
	}

	std::unique_ptr<PostWork> PostJobPtr = std::make_unique<PostWork>();
	PostJobPtr->work = _work;
	m_Iocp.PostQueued(static_cast<DWORD>(WORK_MSG::PostWork), reinterpret_cast<ULONG_PTR>(PostJobPtr.get()));

	PostJobPtr.release();
}

bool ServerQueue::RegistSocket(SOCKET _socket, const std::function<void(BOOL, DWORD, LPOVERLAPPED)>* _onIOCallback) const
{
	if (nullptr == _onIOCallback)
	{
		ServerDebug::AssertDebugMsg("_onIOCallback is nullptr");
		return false;
	}

	if (false == m_Iocp.BindHandle(reinterpret_cast<HANDLE>(_socket), reinterpret_cast<ULONG_PTR>(_onIOCallback)))
	{
		return false;
	}

	return true;
}

void ServerQueue::Initialize(int threadCount, const std::string& _ThreadName)
{
	m_Iocp.Initialize(std::bind(&ServerQueue::WorkThread, this, std::placeholders::_1, _ThreadName), threadCount);
}

void ServerQueue::Destroy()
{
	// IOCP 스레드 종료코드
	for (int i = 0; i < m_Iocp.GetThreadCount(); ++i)
	{
		m_Iocp.PostQueued((DWORD)ServerQueue::WORK_MSG::WORK_DESTROY, 0);
		Sleep(1);
	}
}

