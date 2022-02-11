#include "ClientSerializer.h"
#include <cassert>

ClientSerializer::ClientSerializer(int _bufferSizeByte)
	: m_offset{}
	, m_readOnly(false)
{
	m_buffer.resize(_bufferSizeByte);
}

ClientSerializer::ClientSerializer()
	: ClientSerializer(1024)
{
}

ClientSerializer::ClientSerializer(const std::vector<uint8_t>& _buffer)
	: m_buffer(_buffer)
	, m_offset{}
	, m_readOnly(true)
{
}

ClientSerializer::~ClientSerializer()
{
}

void ClientSerializer::Write(const void* _data, int _size)
{
	// 읽기전용인 경우 쓰기 불가
	assert(false == m_readOnly);

	// 경계값 체크
	assert(m_offset - 1 + _size < m_buffer.size());

	memcpy_s(&m_buffer[m_offset], _size, _data, _size);
	m_offset += _size;
}

void ClientSerializer::operator<<(int _value)
{
	Write(&_value, sizeof(int));
}

void ClientSerializer::operator<<(const std::string& _value)
{
	size_t size = _value.size();
	Write(&size, sizeof(size_t));
	Write(_value.c_str(), _value.size());
}

void ClientSerializer::Read(void* _data, int _size)
{
	// 쓰기전용인 경우 읽기 불가
	assert(true == m_readOnly);

	// 경계값 체크
	assert(m_offset - 1 + _size < m_buffer.size());

	memcpy_s(_data, _size, &m_buffer[m_offset], _size);
	m_offset += _size;
}

void ClientSerializer::operator>>(int& _value)
{
	Read(&_value, sizeof(int));
}

void ClientSerializer::operator>>(std::string& _value)
{
	size_t size;
	Read(&size, sizeof(size_t));
	_value.resize(size);
	Read(&_value[0], size);
}
