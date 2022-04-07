#pragma once

enum class PacketType 
{
	Login,
	Join,
	CreateCharacter,
	SelectCharacter,
	DeleteCharacter,
	LoginResult,
	JoginResult,
	CharacterList,
	CreateCharacterResult,
	DeleteCharacterResult,
	SelectCharacterResult,
	InsertSectionResult,
	ChatMessage,
	MAX
};