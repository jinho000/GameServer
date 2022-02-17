#pragma once
#include "GameServerBase/ServerString.h"

// 单捞磐 流纺拳 贸府
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
	void operator<<(const std::string& _value);

	// read
	void Read(void* _data, int size);
	void operator>>(int& _value);
	void operator>>(std::string& _value);

public:
	const std::vector<uint8_t>& GetBuffer() { return m_buffer; }
};

