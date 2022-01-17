#pragma once

// �뵵 : 
// �з� :
// ÷�� : �ּ�ü�踦 ����ϴ� Ŭ������ �������� �������̽� 
class SocketAddress;
class EndPoint
{
public: // default
	EndPoint() {};
	virtual ~EndPoint() = 0;

	virtual AddressFamily GetAddressFamily() const = 0;

	virtual SocketAddress Serialize() const = 0;

	virtual uint64_t GetHashCode() const = 0;
};
