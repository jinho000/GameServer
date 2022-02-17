#pragma once

enum class PacketType
{
	LOGIN,
	LOGIN_RESULT,
	CHAT_MESSAGE
};

enum class EResultCode
{
	NONE = -1,
	OK,
	PACKET_ERROR,
	MAX
};
