#pragma once

enum class PacketType 
{
	Login,
	Join,
	CreateCharacter,
	LoginResult,
	JoginResult,
	CharacterList,
	CreateCharacterResult,
	ChatMessage,
	MAX
};