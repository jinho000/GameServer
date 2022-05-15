#pragma once

enum class PacketType 
{
	Login,
	Join,
	CreateCharacter,
	SelectCharacter,
	DeleteCharacter,
	UDPStart,
	LoginResult,
	JoginResult,
	CharacterList,
	CreateCharacterResult,
	DeleteCharacterResult,
	SelectCharacterResult,
	InsertSectionResult,
	UDPStartResult,
	ChatMessage,
	PlayerUpdate,
	MAX
};