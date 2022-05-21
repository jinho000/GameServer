#include "pch.h"
#include "ServerSerializer.h"

// 언리얼에서 사용하기위한 헤더
#include <cassert>

ServerSerializer::ServerSerializer(int _bufferSizeByte)
	: m_offset{}
	, m_readOnly(false)
{
	m_buffer.resize(_bufferSizeByte);
}

ServerSerializer::ServerSerializer()
	: ServerSerializer(1024)
{
}

ServerSerializer::ServerSerializer(const std::vector<uint8_t>& _buffer)
	: m_buffer(_buffer)
	, m_offset{}
	, m_readOnly(true)
{
}

ServerSerializer::~ServerSerializer()
{
}

void ServerSerializer::Write(const void* _data, int _size)
{
	// 읽기전용인 경우 쓰기 불가
	assert(false == m_readOnly);

	// 경계값 체크
	assert(m_offset - 1 + _size < m_buffer.size());

	memcpy_s(&m_buffer[m_offset], _size, _data, _size);
	m_offset += _size;
}

void ServerSerializer::operator<<(int _value)
{
	Write(&_value, sizeof(int));
}

void ServerSerializer::operator<<(UINT _value)
{
	Write(&_value, sizeof(UINT));
}

void ServerSerializer::operator<<(uint64_t _value)
{
	Write(&_value, sizeof(uint64_t));
}

void ServerSerializer::operator<<(float _value)
{
	Write(&_value, sizeof(float));
}

void ServerSerializer::operator<<(const std::string& _value)
{
	size_t size = _value.size();
	Write(&size, sizeof(size_t));
	Write(_value.c_str(), static_cast<int>(_value.size()));
}

void ServerSerializer::operator<<(const FVector4& _Value)
{
	Write(&_Value, sizeof(FVector4));
}

void ServerSerializer::Read(void* _data, int _size)
{
	// 쓰기전용인 경우 읽기 불가
	assert(true == m_readOnly);

	// 경계값 체크
	assert(m_offset - 1 + _size < m_buffer.size());

	memcpy_s(_data, _size, &m_buffer[m_offset], _size);
	m_offset += _size;
}

void ServerSerializer::operator>>(int& _value)
{
	Read(&_value, sizeof(int));
}

void ServerSerializer::operator>>(UINT& _value)
{
	Read(&_value, sizeof(UINT));
}

void ServerSerializer::operator>>(uint64_t& _value)
{
	Read(&_value, sizeof(uint64_t));
}

void ServerSerializer::operator>>(float& _value)
{
	Read(&_value, sizeof(float));
}

void ServerSerializer::operator>>(std::string& _value)
{
	size_t size;
	Read(&size, sizeof(size_t));
	_value.resize(size);
	Read(&_value[0], static_cast<int>(size));
}

void ServerSerializer::operator>>(FVector4& _Value)
{
	Read(&_Value, sizeof(FVector4));
}
