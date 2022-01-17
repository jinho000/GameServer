#pragma once

// 용도 : IP 주소값 처리 클래스
// 분류 :
// 첨언 : 주소값을 받아 네트워크바이트오더 값으로 처리
class IPAddress
{
private: // member var
	__int64			m_Address;
	AddressFamily	m_AddressFamily;
	bool			m_bInvalidAddress;

public:
	static IPAddress ParseToIPv4(const std::string& _ip);
	static __int64 ParseToIPv4Int64(const std::string& _ip);

public: // default
	IPAddress() = delete;
	IPAddress(std::string ip);
	IPAddress(__int64 _NetworkByteOrderAddr);
	~IPAddress() = default;

	IPAddress(const IPAddress& _other) noexcept;
	IPAddress(IPAddress&& _other) noexcept;
	IPAddress& operator=(const IPAddress& _other) noexcept;
	IPAddress& operator=(IPAddress&& _other) noexcept;

private:

public: // member func
	__int64 GetAddress() const;
	AddressFamily GetAddressFaimly() const;
	bool IsValidAddress() const;
};

