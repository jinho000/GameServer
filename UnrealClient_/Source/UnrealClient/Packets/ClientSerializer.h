#pragma once
#include <vector>
#include <string>

// Ŭ���̾�Ʈ ��ü ����ȭ Ŭ����
// int: [4����Ʈ ������]
// string: [���ڿ� ������] [���ڿ� ������]
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
	void operator<<(const std::string& _value);

	// read
	void Read(void* _data, int size);
	void operator>>(int& _value);
	void operator>>(std::string& _value);

public:
	const std::vector<uint8_t>& GetBuffer() { return m_buffer; }
};
