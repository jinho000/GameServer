#include "pch.h"
#include "ServerSectionManager.h"

ServerSectionManager* ServerSectionManager::Inst = new ServerSectionManager();

void ServerSectionManager::Init(UINT _threadCount)
{
	for (uint64_t i = 0; i < _threadCount; i++)
	{
		std::shared_ptr<ServerSectionThread> NewThread = std::make_shared<ServerSectionThread>();
		NewThread->StartThread(static_cast<int>(i));
		NewThread->SetName("SectionThread " + std::to_string(i));
		m_allAectionThread.push_back(NewThread);
	}
}

void ServerSectionManager::AddWorkToThread(uint64_t ThreadIndex, uint64_t SectionIndex, uint64_t ObjectId, std::shared_ptr<ServerPacketBase> _Message)
{

}

ServerSectionManager::~ServerSectionManager()
{
	for (size_t i = 0; i < m_allAectionThread.size(); i++)
	{
		m_allAectionThread[i]->Destroy();
	}

	for (size_t i = 0; i < m_allAectionThread.size(); i++)
	{
		m_allAectionThread[i]->Join();
	}
}

void ServerSectionManager::InsertSection(int _ThreadOrder, uint64_t _sectionType, std::shared_ptr<ServerSection> _Section)
{
	if (nullptr == _Section)
	{
		return;
	}

	m_allSection.insert(std::unordered_map<uint64_t, std::shared_ptr<ServerSection>>::value_type(_sectionType, _Section));
	m_allAectionThread[_ThreadOrder]->AddSection(_Section);
	
	return;
}

