#include "PacketHandlerBase.h"

PacketHandlerBase::PacketHandlerBase()
	: m_pGameInst(nullptr)
	, m_pWorld(nullptr)

{
}

PacketHandlerBase::~PacketHandlerBase()
{
}

void PacketHandlerBase::Init(UCGameInstance* _Inst, UWorld* _World)
{
	m_pGameInst = _Inst;
	m_pWorld = _World;
}

