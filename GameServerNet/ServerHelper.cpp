#include "pch.h"
#include "ServerHelper.h"

bool ServerHelper::InitSocketLib()
{
	static bool libSetUpCheck = false;
	if (false == libSetUpCheck)
	{
		WSAData wsData;
		int errorCode = WSAStartup(MAKEWORD(2, 2), &wsData);
		if (SOCKET_ERROR == errorCode)
		{
			ServerDebug::LogError("socket lib error");
			return false;
		}

		libSetUpCheck = true;
	}

	return true;
}

ServerHelper::ServerHelper()
{
}

ServerHelper::~ServerHelper()
{
}

ServerHelper::ServerHelper(ServerHelper&& _other) noexcept
{
}
