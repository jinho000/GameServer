#pragma once
#include <GameServerBase/ServerThread.h>
#include <GameServerBase/ServerIOCP.h>
#include "ServerSection.h"

// �����忡�� ������ ó��
class ServerSectionThread : public ServerThread
{
private: // member var
	std::map<uint64_t, std::shared_ptr<ServerSection>> m_KeySections_;
	std::vector<std::shared_ptr<ServerSection>> m_allSection;
	
	ServerIOCP IOCP; // thread�� ���� �ޱ� ���� IOCP

	// insert
	// ���� �߰��ÿ��� ���� ����
	// ó���� ���ǰ����� ������ ����� ��� �ʿ����
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

