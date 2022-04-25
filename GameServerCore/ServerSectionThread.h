#pragma once
#include <GameServerBase/ServerThread.h>
#include <GameServerBase/ServerIOCP.h>
#include "ServerSection.h"

// 스레드에서 섹션을 처리
class ServerSectionThread : public ServerThread
{
private: // member var
	std::map<uint64_t, std::shared_ptr<ServerSection>> m_KeySections_;
	std::vector<std::shared_ptr<ServerSection>> m_allSection;
	
	ServerIOCP IOCP; // thread에 일을 받기 위한 IOCP

	// insert
	// 섹션 추가시에만 락을 걸음
	// 처음에 섹션개수를 고정후 사용할 경우 필요없음
	std::mutex InsertLock_;
	std::atomic<size_t> InsertSectionSize_;
	std::vector<std::shared_ptr<ServerSection>> InsertSections_;

public: // default
	ServerSectionThread();
	~ServerSectionThread();

	ServerSectionThread(const ServerSectionThread& _other) = delete;
	ServerSectionThread(ServerSectionThread&& _other) = delete;
	ServerSectionThread& operator=(const ServerSectionThread& _other) = delete;
	ServerSectionThread& operator=(const ServerSectionThread&& _other) = delete;

private:
	void SectionThreadWork(UINT _threadOrder);

public: // member Func
	void AddSection(std::shared_ptr<ServerSection> _Section);
	void StartThread(UINT _threadOrder);
	void Destroy();
};

