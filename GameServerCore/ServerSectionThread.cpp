#include "pch.h"
#include "ServerSectionThread.h"
#include <GameServerBase/ServerQueue.h>

ServerSectionThread::ServerSectionThread()
{
}

ServerSectionThread::~ServerSectionThread()
{
}

// 섹션 스레드 함수
void ServerSectionThread::SectionThreadWork(UINT _threadOrder)
{
	SetThreadName(GetNameCopy());
	SetThreadOrder(_threadOrder);
	IOCP.InitHandle(1);

	bool isExit = false;
	while (isExit == false)
	{
		// 스레드에 들어온일을 처리
		while (true)
		{
			// 나는 이미 IOCP를 가지고 있고.
			DWORD NumberOfBytesTransferred;
			ULONG_PTR CompletionKey;
			LPOVERLAPPED lpOverlapped;

			// POST된게 있으면 빼준다.
			BOOL Result = IOCP.Execute(NumberOfBytesTransferred, CompletionKey, lpOverlapped, 1);

			// 뭔가 문제가 있다는 건데.
			if (FALSE == Result)
			{
				if (WAIT_TIMEOUT == GetLastError())
				{
					break;
				}

				// 말그대로 아무것도 없어서 그냥 나온겁니다.
				// 타임아웃이건 뭐건 일이 없다.
				break;
			}

			int MessageType = static_cast<int>(NumberOfBytesTransferred);
			switch (MessageType)
			{
			case -1:
				// 종료
				isExit = true;
				break;
			default:
				if (0 != CompletionKey)
				{
					//PostJob* JobTesk = reinterpret_cast<PostJob*>(CompletionKey);
					//JobTesk->task_();
				}
				break;
			}

			if (isExit)
			{
				break;
			}
		}

		// Thread마다 타이머를 가져야 동기화 문제와 시간 문제에 대해서 신경쓰지 않을수 있다.
		float DelataTime = Timer.Update();
		for (size_t i = 0; i < m_allSection.size(); i++)
		{
			// 이게 한프레임
			//m_allSection[i]->AccTimeUpdate(DelataTime);
			m_allSection[i]->Update(DelataTime);
			m_allSection[i]->Release();
		}


		if (m_insertSection.empty() == false)
		{
			// 스레드 실행중 다른 섹션이 추가되면 여기서 락을걸고 추가한다
			std::lock_guard lock(m_insertLock);
			for (const std::shared_ptr<ServerSection>& section : m_insertSection)
			{
				m_allSection.push_back(section);
			}

			m_insertSection.clear();
		}

		Sleep(1);
	}
}

void ServerSectionThread::AddSection(const std::shared_ptr<ServerSection>& _section)
{
	// 스레드에서 몇번째 섹션인지 설정
	_section->SetSectionIndex(static_cast<UINT>(m_allSection.size()));
	m_insertSection.push_back(_section);
}

void ServerSectionThread::StartThread(UINT _threadOrder)
{
	Start(std::bind(&ServerSectionThread::SectionThreadWork, this, _threadOrder));
}

void ServerSectionThread::Destroy()
{
	IOCP.PostQueued(static_cast<DWORD>(ServerQueue::WORK_MSG::WORK_DESTROY), 0);
	Sleep(1);
}
