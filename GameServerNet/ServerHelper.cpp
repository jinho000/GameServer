#include "pch.h"
#include "ServerHelper.h"
#include "GameServerBase/ServerDebug.h"

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

std::string ServerHelper::GetMyIP()
{
	InitSocketLib();

    char hostName[255] = {};

    // 성공할경우 0 반환, 실패시 -1 (SOCKET_ERROR )반환
    
    if (0 != gethostname(hostName, 255))
    {
        ServerDebug::AssertDebugMsg("Host Name Error");
        return std::string();
    }

    // 실패시 nullptr
    HOSTENT* hostInfo = gethostbyname(hostName);
    if (nullptr == hostInfo)
    {
        ServerDebug::AssertDebugMsg("HostInfo Error");
        return std::string();
    }

    // IP 주소값 가져오기
    IN_ADDR sinAddr = {};

    // IPv4 주소체계만 사용
    if (AF_INET != hostInfo->h_addrtype)
    {
        ServerDebug::AssertDebugMsg("Address Family Error");
        return std::string();
    }

    // 맨처음 IP를 서버아이피로 사용
    std::string myIP;
    if (0 != hostInfo->h_addr_list[0])
    {
        memcpy(&sinAddr, hostInfo->h_addr_list[0], hostInfo->h_length);//메모리 복사
        myIP = (inet_ntoa(sinAddr));
    }

	return myIP;
}

