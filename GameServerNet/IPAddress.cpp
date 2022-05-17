#include "pch.h"
#include "IPAddress.h"
#include <WS2tcpip.h> // inet_pton 함수 헤더
#include "GameServerBase/ServerDebug.h"

IPAddress IPAddress::ParseToIPv4(const std::string& _ip)
{	
	return IPAddress(_ip);
}

__int64 IPAddress::ParseToIPv4Int64(const std::string& _ip)
{
	if (true == _ip.empty())
	{
		return -1;
	}

	// 소문자 변환
	std::string strIP = _ip;
	std::transform(strIP.begin(), strIP.end(), strIP.begin(), ::tolower);

	// localhost, 0.0.0.0으로 받은경우 처리
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	if (strIP == "localhost")
	{
		inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr.s_addr);
	}
	else if (strIP == "0.0.0.0")
	{
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		if (1 != inet_pton(AF_INET, strIP.c_str(), &sin.sin_addr.s_addr))
		{
			ServerDebug::AssertDebugMsg("IP Error");
			return -1;
		}
	}

	return sin.sin_addr.s_addr;
}

IPAddress::IPAddress(std::string _ip)
	: m_Address(ParseToIPv4Int64(_ip))
	, m_AddressFamily(AddressFamily::IPV4)
	, m_bInvalidAddress(true)

{
	if (m_Address == -1)
	{
		m_bInvalidAddress = false;
	}
}

IPAddress::IPAddress(__int64 _NetworkByteOrderAddr)
	: m_Address(0)
	, m_AddressFamily(AddressFamily::IPV4)
{
	m_bInvalidAddress = _NetworkByteOrderAddr < 0 || _NetworkByteOrderAddr>0x00000000FFFFFFFF;
	m_Address = _NetworkByteOrderAddr;
}


IPAddress::IPAddress(const IPAddress& _other) noexcept
	: m_Address(_other.m_Address)
	, m_AddressFamily(_other.m_AddressFamily)
	, m_bInvalidAddress(_other.m_bInvalidAddress)
{
}

IPAddress::IPAddress(IPAddress&& _other) noexcept
	: m_Address(_other.m_Address)
	, m_AddressFamily(_other.m_AddressFamily)
	, m_bInvalidAddress(_other.m_bInvalidAddress)
{
	m_Address = -1;
	m_AddressFamily = AddressFamily::UNKNOWN;
	m_bInvalidAddress = false;
}

IPAddress& IPAddress::operator=(const IPAddress& _other) noexcept
{
	m_Address = _other.m_Address;
	m_AddressFamily = _other.m_AddressFamily;
	m_bInvalidAddress = _other.m_bInvalidAddress;

	return *this;
}

IPAddress& IPAddress::operator=(IPAddress&& _other) noexcept
{
	m_Address = _other.m_Address;
	m_AddressFamily = _other.m_AddressFamily;
	m_bInvalidAddress = _other.m_bInvalidAddress;

	_other.m_Address = -1;
	_other.m_AddressFamily = AddressFamily::UNKNOWN;
	_other.m_bInvalidAddress = false;

	return *this;
}

__int64 IPAddress::GetAddress() const
{
	return m_Address;
}

AddressFamily IPAddress::GetAddressFaimly() const
{
	return m_AddressFamily;
}

bool IPAddress::IsValidAddress() const
{
	return m_bInvalidAddress;
}
