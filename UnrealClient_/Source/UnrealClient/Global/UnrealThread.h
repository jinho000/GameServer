// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <memory>

#include "../Packets/ClientPackets/ClientPacketBase.h"


//리시브 처리는 다른 스레드에서 처리
//->메인스레드에서 처리할경우
//동기 리시브 : 메인 로직이 멈춤
//비동기 리시브 : 메인스레드에서 이벤트를 계속 확인해야함
// 
// recv를 처리하기 위한 스레드
class UnrealThread : public FRunnable
{
private:
	FSocket*									m_recvSocket;
	TQueue<std::shared_ptr<ClientPacketBase>>*	m_pRecvQueue;

public:
	UnrealThread() = delete;
	UnrealThread(FSocket* _socket, TQueue<std::shared_ptr<ClientPacketBase>>* _recvQueue);
	~UnrealThread();

public:
	uint32 Run() override;
	void Stop() override;
	void Exit() override;
};
