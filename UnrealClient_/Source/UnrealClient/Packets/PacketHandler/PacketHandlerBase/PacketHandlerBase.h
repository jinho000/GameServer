#pragma once
#include <memory>
#include "../../ClientPackets/Packets.h"
#include "../../../Global/CGameInstance.h"

// PacketHandlerBase.cpp ÆÄÀÏ ¸¸µé¸é ºôµå ¾ÈµÊ

template <class PacketType>
class PacketHandlerBase
{
protected: // member var
	class UCGameInstance*		m_pGameInst;
	class UWorld*				m_pWorld;
	std::shared_ptr<PacketType> m_packet;

public:
	virtual ~PacketHandlerBase() = default;

public: // member Func
	virtual void Start() = 0;
	virtual void Init(UCGameInstance* _Inst, UWorld* _World, std::shared_ptr<PacketType> _packet)
	{
		m_pGameInst = _Inst;
		m_pWorld = _World;
		m_packet = _packet;
	}
};


