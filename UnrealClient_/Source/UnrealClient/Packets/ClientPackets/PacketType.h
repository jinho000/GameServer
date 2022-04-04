#pragma once

enum class PacketType 
{
	Login,
	Join,
	CreateCharacter,
	SelectCharacter,
	LoginResult,
	JoginResult,
	CharacterList,
	CreateCharacterResult,
	SelectCharacterResult,
	InsertSectionResult,
	ChatMessage,
	MAX
};