#pragma once

enum class PacketType 
{
	Login,
	Join,
	CreateCharacter,
	SelectCharacter,
	DeleteCharacter,
	UDPStart,
	PlayerUpdate,
	LoginResult,
	JoginResult,
	CharacterList,
	CreateCharacterResult,
	DeleteCharacterResult,
	SelectCharacterResult,
	InsertSectionResult,
	UDPStartResult,
	AllPlayerInfo,
	SpawnOtherPlayer,
	ChatMessage,
	PlayerComeIn,
	MAX
};