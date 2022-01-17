#include "pch.h"
#include "SocketAddress.h"
#include "IPAddress.h"
#include "IPEndPoint.h"

void SocketAddress::Initialize()
{
    if (nullptr == m_pBuffer)
    {
        m_BufferMaxSize = sizeof(SOCKADDR_IN) < sizeof(SOCKADDR_IN6) ? sizeof(SOCKADDR_IN6) : sizeof(SOCKADDR_IN);
        m_pBuffer = new char[m_BufferMaxSize];
    }

    m_BufferLength = 0;
    memset(m_pBuffer, 0x00, m_BufferMaxSize);
}

void SocketAddress::Destroy()
{
    if (nullptr != m_pBuffer)
    {
        delete[] m_pBuffer;
    }

    m_pBuffer = nullptr;
    m_BufferLength = 0;
    m_BufferMaxSize = 0;
}

SocketAddress::SocketAddress(const IPAddress& _ipAddress, int port)
    : m_pBuffer(nullptr)
    , m_BufferMaxSize(0)
    , m_BufferLength(0)
{
    Initialize();

    m_BufferLength = sizeof(SOCKADDR_IN6);
    if (AddressFamily::IPV4 == _ipAddress.GetAddressFaimly())
    {
        m_BufferLength = sizeof(SOCKADDR_IN);
    }

    int family = static_cast<int>(_ipAddress.GetAddressFaimly());

    // buffer에 값 밀어넣기

    // 2바이트: 주소체계
    m_pBuffer[0] = static_cast<char>(family);
    m_pBuffer[1] = static_cast<char>((family >> 8));

    // 2바이트: 포트값
    m_pBuffer[2] = static_cast<char>(port >> 8);
    m_pBuffer[3] = static_cast<char>(port);

    // 4바이트: 주소값
    __int64 i64Address = _ipAddress.GetAddress();

    m_pBuffer[4] = static_cast<char>(i64Address);
    m_pBuffer[5] = static_cast<char>((i64Address >> 8));
    m_pBuffer[6] = static_cast<char>((i64Address >> 16));
    m_pBuffer[7] = static_cast<char>((i64Address >> 24));
}

SocketAddress::SocketAddress(const IPEndPoint& _ipEndPoint)
    : SocketAddress(_ipEndPoint.GetIPAddress(), _ipEndPoint.GetPort())
{
}

SocketAddress::~SocketAddress()
{
    Destroy();
}

const char* SocketAddress::GetBuffer() const
{
    return m_pBuffer;
}

size_t SocketAddress::GetBufferLength() const
{
    return m_BufferLength;
}

AddressFamily SocketAddress::GetAddressFamily() const
{
    int family = m_pBuffer[0] | (m_pBuffer[1] << 8);
    return static_cast<AddressFamily>(family);
}

int SocketAddress::GetPort() const
{
    int port = m_pBuffer[2] << 8 & 0xFF00 | m_pBuffer[3] & 0xFF;
    return port;
}

IPAddress SocketAddress::GetIPAddress() const
{
    __int64 address = static_cast<__int64>(
        (m_pBuffer[4] & 0x000000FF) |
        (m_pBuffer[5] << 8 & 0x0000FF00) |
        (m_pBuffer[6] << 16 & 0x00FF0000) |
        (m_pBuffer[7] << 24 & 0xFF000000)
        ) & 0x00000000FFFFFFFF;

    return IPAddress(address);
}

IPEndPoint SocketAddress::GetIPEndPoint() const
{
    IPAddress address = GetIPAddress();
    int port = GetPort();

    return IPEndPoint(address, port);
}

SocketAddress::SocketAddress(const SocketAddress& _other)
    : m_pBuffer(nullptr)
    , m_BufferMaxSize(_other.m_BufferMaxSize)
    , m_BufferLength(_other.m_BufferLength)
{
    if (nullptr != _other.m_pBuffer)
    {
        m_pBuffer = new char[m_BufferMaxSize];
        memcpy_s(m_pBuffer, m_BufferMaxSize, _other.m_pBuffer, _other.m_BufferLength);
    }
}

SocketAddress::SocketAddress(SocketAddress&& _other) noexcept
    : m_pBuffer(_other.m_pBuffer)
    , m_BufferMaxSize(_other.m_BufferMaxSize)
    , m_BufferLength(_other.m_BufferLength)
{
    _other.m_pBuffer = nullptr;
    _other.m_BufferMaxSize = 0;
    _other.m_BufferLength = 0;
}

SocketAddress& SocketAddress::operator=(const SocketAddress& _other)
{
    Destroy();

    m_BufferMaxSize = _other.m_BufferMaxSize;
    m_BufferLength = _other.m_BufferLength;
    if (nullptr != _other.m_pBuffer)
    {
        m_pBuffer = new char[m_BufferMaxSize];
        memcpy_s(m_pBuffer, m_BufferMaxSize, _other.m_pBuffer, _other.m_BufferLength);
    }

    return *this;
}

SocketAddress& SocketAddress::operator=(SocketAddress&& _other) noexcept
{
    Destroy();

    m_pBuffer = _other.m_pBuffer;
    m_BufferMaxSize = _other.m_BufferMaxSize;
    m_BufferLength = _other.m_BufferLength;

    _other.m_pBuffer = nullptr;
    _other.m_BufferMaxSize = 0;
    _other.m_BufferLength = 0;

    return *this;
}
