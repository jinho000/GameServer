#pragma once
#include "CoreMinimal.h"
#include <memory>

#include "../Packets/ClientPackets/ServerPacketBase.h"

class UnrealUDPThread : public FRunnable
{
private: // member var
	ISocketSubsystem*	m_socketSubSystem;
	TAtomic<bool>		m_bAppClose;
	TAtomic<bool>		m_bRun;
	FSocket*			m_recvSocket;
	TQueue<std::shared_ptr<ServerPacketBase>>* m_pRecvQueue;

public: // default
	UnrealUDPThread(ISocketSubsystem* _socketSubSystem, FSocket* _socket, TQueue<std::shared_ptr<ServerPacketBase>>* _recvQueue);
	~UnrealUDPThread();

	UnrealUDPThread(const UnrealUDPThread& _other) = delete;
	UnrealUDPThread(UnrealUDPThread&& _other) = delete;
	UnrealUDPThread& operator=(const UnrealUDPThread& _other) = delete;
	UnrealUDPThread& operator=(const UnrealUDPThread&& _other) = delete;

public: // member Func
	uint32 Run() override;
	void Destroy();

	void RunThread();
	void StopThread();
};

