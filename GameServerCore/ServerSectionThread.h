#pragma once
#include <GameServerBase/ServerThread.h>
#include <GameServerBase/ServerIOCP.h>
#include "ServerSection.h"

// 스레드에서 섹션을 처리
class ServerSectionThread : public ServerThread
{
private: // member var
	std::vector<std::shared_ptr<ServerSection>> m_allSection; // 스레드에서 관리하는 섹션
	
	ServerIOCP IOCP; // thread에 일을 받기 위한 IOCP

	// insert
	// 섹션 추가시에만 락을 걸음
	// 처음에 섹션개수를 고정후 사용할 경우 필요없음
	std::mutex m_insertLock;
	std::vector<std::shared_ptr<ServerSection>> m_insertSection;

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
	void AddSection(const std::shared_ptr<ServerSection>& _section);
	void StartThread(UINT _threadOrder);
	void Destroy();

	void Enqueue();
};

