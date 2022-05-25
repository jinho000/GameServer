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
	RequestMath,
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
	GameMatch,
	ChatMessage,
	MAX
};