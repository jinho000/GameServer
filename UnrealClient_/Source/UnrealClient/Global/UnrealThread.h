// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <memory>

#include "../Packets/ClientPackets/ClientPacketBase.h"


//���ú� ó���� �ٸ� �����忡�� ó��
//->���ν����忡�� ó���Ұ��
//���� ���ú� : ���� ������ ����
//�񵿱� ���ú� : ���ν����忡�� �̺�Ʈ�� ��� Ȯ���ؾ���
// 
// recv�� ó���ϱ� ���� ������
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
