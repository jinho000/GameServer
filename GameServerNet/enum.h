#pragma once

enum class AddressFamily
{
	UNKNOWN = - 1,
	UNSPECIFIED = 0,
	IPV4 = 2,	// AF_INET
	IPV6 = 23,	// AF_INET6
	MAX = 29
};
