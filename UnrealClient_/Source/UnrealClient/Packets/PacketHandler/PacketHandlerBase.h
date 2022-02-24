#pragma once
#include <memory>
#include "../ClientPackets/ServerAndClient.h"
#include "../ClientPackets/ServerToClient.h"
#include "../ClientPackets/ClientToServer.h"


// 패킷 핸들러 기본 클래스
class UCGameInstance;
class UWorld;
class PacketHandlerBase
{
protected: // member var
	UCGameInstance*	m_pGameInst;
	UWorld*			m_pWorld;

public: // default
	PacketHandlerBase();
	virtual ~PacketHandlerBase();

	PacketHandlerBase(const PacketHandlerBase& _other) = delete;
	PacketHandlerBase(PacketHandlerBase&& _other) = delete;

protected:
	PacketHandlerBase& operator=(const PacketHandlerBase& _other) = delete;
	PacketHandlerBase& operator=(const PacketHandlerBase&& _other) = delete;

private:

public: // member Func
	virtual void Start() = 0;
	virtual void Init(UCGameInstance* _Inst, UWorld* _World);
};

