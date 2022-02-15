#pragma once

enum class PacketType
{
	LOGIN,
	LOGIN_RESULT
};

enum class EResultCode
{
	NONE = -1,
	OK,
	PACKET_ERROR,
	MAX
};
