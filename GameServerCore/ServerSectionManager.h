#pragma once
#include "ServerSection.h"
#include "ServerSectionThread.h"

// Section을 관리하는 매니저
// 여러개의 스레드를 두고 스레드에서 섹션을 관리
// 매니저를 통해 스레드에 접근, 섹션에 일을 시킴
// 

class ServerPacketBase;
class ServerSectionManager
{
private: // member var
	static ServerSectionManager* Inst;

private:
	std::unordered_map<uint64_t, std::shared_ptr<ServerSection>> m_allSection;
	std::vector<std::shared_ptr<ServerSectionThread>> m_allAectionThread;

private: // default
	ServerSectionManager() = default;
	~ServerSectionManager();

	ServerSectionManager(const ServerSectionManager& _other) = delete;
	ServerSectionManager(ServerSectionManager&& _other) = delete;
	ServerSectionManager& operator=(const ServerSectionManager& _other) = delete;
	ServerSectionManager& operator=(const ServerSectionManager&& _other) = delete;

private:
	void InsertSection(int _ThreadOrder, uint64_t _sectionType, std::shared_ptr<ServerSection> _Section);

	template<typename SectionType, typename ... Parameter>
	std::shared_ptr<SectionType> CreateSection(int _ThreadOrder, uint64_t _sectionType, Parameter ... Arg)
	{
		std::shared_ptr<SectionType> NewSection = std::make_shared<SectionType>(Arg...);
		NewSection->SetSectionIndex(_sectionType);
		NewSection->SetThreadOrder(_ThreadOrder);
		NewSection->Init();
		InsertSection(_ThreadOrder, _sectionType, NewSection);

		return NewSection;
	}

public:
	static ServerSectionManager* GetInst()
	{
		return Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	void Init(UINT _threadCount);
	
	template<typename SectionType, typename EnumType, typename ... Parameter>
	std::shared_ptr<SectionType> CreateSection(int _ThreadOrder, EnumType _sectionType, Parameter ... Arg)
	{
		return CreateSection<SectionType>(_ThreadOrder, static_cast<uint64_t>(_sectionType), Arg...);
	}

	void AddWorkToThread(uint64_t ThreadIndex, uint64_t SectionIndex, uint64_t ObjectId, std::shared_ptr<ServerPacketBase> _Message);

};

