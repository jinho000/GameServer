#include "pch.h"
#include "IPEndPoint.h"
#include "SocketAddress.h"

IPEndPoint::IPEndPoint(const std::string& _ip, int _port)
	: m_ipAddress(_ip)
	, m_port(_port)
{
}

IPEndPoint::IPEndPoint()
	: m_ipAddress("localhost")
	, m_port(30000)
{
}

IPEndPoint::IPEndPoint(__int64 address, int port) 
	: m_port(port)
	, m_ipAddress(address)
{
}

IPEndPoint::IPEndPoint(const IPAddress& _ipAddress, int _port)
	: m_ipAddress(_ipAddress)
	, m_port(_port)
{
}

IPEndPoint::IPEndPoint(const IPEndPoint& _other)
	: m_ipAddress(_other.m_ipAddress)
	, m_port(_other.m_port)
{
}

IPEndPoint::IPEndPoint(IPEndPoint&& _other) noexcept
	: m_ipAddress(_other.m_ipAddress)
	, m_port(_other.m_port)
{
}

IPEndPoint& IPEndPoint::operator=(const IPEndPoint& _other)
{
	if (this == &_other)
	{
		return *this;
	}

	m_ipAddress = _other.m_ipAddress;
	m_port = _other.m_port;

	return *this;
}

IPEndPoint& IPEndPoint::operator=(const IPEndPoint&& _other) noexcept
{
	if (this == &_other)
	{
		return *this;
	}

	m_ipAddress = _other.m_ipAddress;
	m_port = _other.m_port;

	return *this;
}

bool IPEndPoint::operator==(const IPEndPoint& _endPoint) const
{
	return m_ipAddress.GetAddress() == _endPoint.m_ipAddress.GetAddress() &&
		m_port == _endPoint.m_port;
}

bool IPEndPoint::operator!=(const IPEndPoint& _endPoint) const
{
	return !((*this) == _endPoint);
}

IPEndPoint::~IPEndPoint()
{
}

const IPAddress& IPEndPoint::GetIPAddress() const
{
	return m_ipAddress;
}

int IPEndPoint::GetPort() const
{
	return m_port;
}

AddressFamily IPEndPoint::GetAddressFamily() const
{
	return m_ipAddress.GetAddressFaimly();
}

SocketAddress IPEndPoint::Serialize() const
{
	return SocketAddress(m_ipAddress, m_port);
}

uint64_t IPEndPoint::GetHashCode() const
{
	return (m_ipAddress.GetAddress() << 16) | m_port;
}
