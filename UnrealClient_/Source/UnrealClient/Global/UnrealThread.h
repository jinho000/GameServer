// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <memory>

#include "../Packets/ClientPackets/ServerPacketBase.h"


//리시브 처리는 다른 스레드에서 처리
//->메인스레드에서 처리할경우
// 동기 리시브 : 메인 로직이 멈춤
// 비동기 리시브처리 : 메인스레드에서 이벤트를 계속 확인
// 
// recv를 처리하기 위한 스레드
class UnrealThread : public FRunnable
{
private:
	FSocket*									m_recvSocket;
	TQueue<std::shared_ptr<ServerPacketBase>>*	m_pRecvQueue;
	TAtomic<bool>								m_bAppClose;

public:
	UnrealThread() = delete;
	UnrealThread(FSocket* _socket, TQueue<std::shared_ptr<ServerPacketBase>>* _recvQueue);
	~UnrealThread();

public:
	uint32 Run() override;
	void Stop() override;
	void Exit() override;
};
