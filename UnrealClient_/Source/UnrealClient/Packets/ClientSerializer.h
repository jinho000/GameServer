#pragma once
#include <vector>
#include <string>

// 클라이언트 객체 직렬화 클래스
// int: [4바이트 데이터]
// string: [문자열 사이즈] [문자열 데이터]
class ClientSerializer
{
private: // member var
	std::vector<uint8_t>	m_buffer;
	size_t					m_offset;
	bool					m_readOnly;

public: // default
	// write
	ClientSerializer(int _bufferSizeByte);
	ClientSerializer();
	
	// read
	ClientSerializer(const std::vector<uint8_t>& _buffer);
	
	~ClientSerializer();

	ClientSerializer(const ClientSerializer& _other) = delete;
	ClientSerializer(ClientSerializer&& _other) = delete;

protected:
	ClientSerializer& operator=(const ClientSerializer& _other) = delete;
	ClientSerializer& operator=(const ClientSerializer&& _other) = delete;

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

