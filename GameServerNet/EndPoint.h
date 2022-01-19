#pragma once

// 용도 : 
// 분류 :
// 첨언 : 주소체계를 담당하는 클래스가 가져야할 인터페이스 
class SocketAddress;
class EndPoint
{
public: // default
	EndPoint() = default;
	virtual ~EndPoint() = default;

	virtual AddressFamily GetAddressFamily() const = 0;

	virtual SocketAddress Serialize() const = 0;

	virtual uint64_t GetHashCode() const = 0;
};

