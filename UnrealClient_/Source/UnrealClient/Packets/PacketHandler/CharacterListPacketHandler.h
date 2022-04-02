#pragma once
#include "PacketHandlerBase.h"


class CharacterListPacketHandler : public PacketHandlerBase
{
private: // member var
	std::shared_ptr<CharacterListPacket> m_packet;

public: // default
	CharacterListPacketHandler(const std::shared_ptr<CharacterListPacket>& _packet);
	~CharacterListPacketHandler();

	CharacterListPacketHandler(const CharacterListPacketHandler& _other) = delete;
	CharacterListPacketHandler(CharacterListPacketHandler&& _other) = delete;
	CharacterListPacketHandler& operator=(const CharacterListPacketHandler& _other) = delete;
	CharacterListPacketHandler& operator=(const CharacterListPacketHandler&& _other) = delete;

private:

public: // member Func
	void Start() override;

};

