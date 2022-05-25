#include "pch.h"
#include "ServerSectionManager.h"

ServerSectionManager* ServerSectionManager::Inst = new ServerSectionManager();

void ServerSectionManager::Init(UINT _threadCount)
{
	m_threadCount = _threadCount;

	for (uint64_t i = 0; i < _threadCount; i++)
	{
		std::shared_ptr<ServerSectionThread> NewThread = std::make_shared<ServerSectionThread>();
		NewThread->StartThread(static_cast<int>(i));
		NewThread->SetName("SectionThread " + std::to_string(i));
		m_allSectionThread.push_back(NewThread);
	}
}

void ServerSectionManager::AddSection(const std::shared_ptr<ServerSection>& _section)
{
	int threadOrder = m_allSection.size() % m_threadCount;
	m_allSectionThread[threadOrder]->AddSection(_section);

	// 섹션을 관리할 스레드 번호 설정
	_section->SetThreadOrder(threadOrder);
}

void ServerSectionManager::AddWorkToThread(UINT _threadOrder, const std::shared_ptr<ServerPacketBase>& _packet)
{
	//m_allSectionThread[_threadOrder]->
}

//void ServerSectionManager::AddWorkToThread(uint64_t ThreadIndex, uint64_t SectionIndex, uint64_t ObjectId, std::shared_ptr<ServerPacketBase> _Message)
//{
//
//}

ServerSectionManager::~ServerSectionManager()
{
	for (size_t i = 0; i < m_allSectionThread.size(); i++)
	{
		m_allSectionThread[i]->Destroy();
	}

	for (size_t i = 0; i < m_allSectionThread.size(); i++)
	{
		m_allSectionThread[i]->Join();
	}
}

void ServerSectionManager::InsertSection(int _ThreadOrder, uint64_t _sectionType, std::shared_ptr<ServerSection> _Section)
{
	if (nullptr == _Section)
	{
		return;
	}

	m_allSection_.insert(std::unordered_map<uint64_t, std::shared_ptr<ServerSection>>::value_type(_sectionType, _Section));
	m_allSectionThread[_ThreadOrder]->AddSection(_Section);
	
	return;
}

