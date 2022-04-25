#include "pch.h"
#include "ServerSectionThread.h"
#include <GameServerBase/ServerQueue.h>

ServerSectionThread::ServerSectionThread()
{
}

ServerSectionThread::~ServerSectionThread()
{
}

// ���� ������ �Լ�
void ServerSectionThread::SectionThreadWork(UINT _threadOrder)
{
	SetThreadName(GetNameCopy());
	SetThreadOrder(_threadOrder);
	IOCP.InitHandle(1);

	bool isExit = false;
	while (isExit == false)
	{
		// �����忡 �������� ó��
		while (true)
		{
			// ���� �̹� IOCP�� ������ �ְ�.
			DWORD NumberOfBytesTransferred;
			ULONG_PTR CompletionKey;
			LPOVERLAPPED lpOverlapped;

			// POST�Ȱ� ������ ���ش�.
			BOOL Result = IOCP.Execute(NumberOfBytesTransferred, CompletionKey, lpOverlapped, 1);

			// ���� ������ �ִٴ� �ǵ�.
			if (FALSE == Result)
			{
				if (WAIT_TIMEOUT == GetLastError())
				{
					break;
				}

				// ���״�� �ƹ��͵� ��� �׳� ���°̴ϴ�.
				// Ÿ�Ӿƿ��̰� ���� ���� ����.
				break;
			}

			int MessageType = static_cast<int>(NumberOfBytesTransferred);
			switch (MessageType)
			{
			case -1:
				// ����
				isExit = true;
				break;
			case -2:
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

		// Thread���� Ÿ�̸Ӹ� ������ ����ȭ ������ �ð� ������ ���ؼ� �Ű澲�� ������ �ִ�.
		float DelataTime = Timer.Update();
		for (size_t i = 0; i < m_allSection.size(); i++)
		{
			//if (false == Sections_[i]->IsUpdate())
			//{
			//	continue;
			//}
			
			// �̰� ���������ΰ̴ϴ�.
			m_allSection[i]->AccTimeUpdate(DelataTime);
			m_allSection[i]->Update(DelataTime);
			m_allSection[i]->Release();
		}

		Sleep(1);
	}
}

void ServerSectionThread::AddSection(std::shared_ptr<ServerSection> _Section)
{
	m_allSection.push_back(_Section);
	m_KeySections_.insert(std::make_pair(_Section->GetSectionIndex(), _Section));

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
