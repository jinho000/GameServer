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

public: // member Func
	// Write

	void Write(const void* _data, int size);
	void operator<<(int _value);
	void operator<<(UINT _value);
	void operator<<(uint64_t _value);
	void operator<<(float _value);
	void operator<<(const std::string& _value);
	void operator<<(const FVector4& _Value);

	template<typename T>
	void WriteEnum(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void WriteVector(std::vector<T>& _Value)
	{
		operator<<(static_cast<int>(_Value.size()));
		for (size_t i = 0; i < _Value.size(); i++)
		{
			_Value[i].Serialize(*this);
		}
	}

	// read

	void Read(void* _data, int size);
	void operator>>(int& _value);
	void operator>>(UINT& _value);
	void operator>>(uint64_t& _value);
	void operator>>(float& _value);
	void operator>>(std::string& _value);
	void operator>>(FVector4& _Value);

	template<typename T>
	void ReadEnum(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void ReadVector(std::vector<T>& _Value)
	{
		int Size;
		operator>>(Size);
		_Value.resize(Size);
		for (size_t i = 0; i < _Value.size(); i++)
		{
			_Value[i].Deserialize(*this);
		}
	}

public:
	const std::vector<uint8_t>& GetBuffer() { return m_buffer; }
};

