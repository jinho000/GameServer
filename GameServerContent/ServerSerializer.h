#pragma once
// 언리얼에서 사용하기 위한 헤더
#include <vector>
#include <string>

// 데이터 직렬화 처리
class ServerSerializer
{
private: // member var
	std::vector<uint8_t>	m_buffer;
	size_t					m_offset;
	bool					m_readOnly;

public: // default
	// write
	ServerSerializer(int _bufferSizeByte);
	ServerSerializer();

	// read
	ServerSerializer(const std::vector<uint8_t>& _buffer);

	~ServerSerializer();

	ServerSerializer(const ServerSerializer& _other) = delete;
	ServerSerializer(ServerSerializer&& _other) = delete;

protected:
	ServerSerializer& operator=(const ServerSerializer& _other) = delete;
	ServerSerializer& operator=(const ServerSerializer&& _other) = delete;

private:

public: // member Func
	// Write
	void Write(const void* _data, int size);
	void operator<<(int _value);
	void operator<<(UINT _value);
	void operator<<(const std::string& _value);
	template<typename T>
	void WriteEnum(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	// read
	void Read(void* _data, int size);
	void operator>>(int& _value);
	void operator>>(UINT& _value);
	void operator>>(std::string& _value);

	template<typename T>
	void ReadEnum(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

public:
	const std::vector<uint8_t>& GetBuffer() { return m_buffer; }
};

