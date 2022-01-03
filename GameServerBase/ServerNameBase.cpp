#include "pch.h"
#include "ServerNameBase.h"

ServerNameBase::ServerNameBase(const std::string& _name)
	: m_name(_name)
{
}

ServerNameBase::~ServerNameBase()
{
}

ServerNameBase::ServerNameBase(ServerNameBase&& _other) noexcept
	: m_name(_other.m_name)
{
}

const std::string& ServerNameBase::GetName() const
{
	return m_name;
}

std::string ServerNameBase::GetNameCopy() const
{
	return m_name;
}

std::string_view ServerNameBase::GetNameView() const
{
	return m_name;
}

const char* ServerNameBase::GetNameChar() const
{
	return m_name.c_str();
}

void ServerNameBase::SetName(const std::string& _name)
{
	m_name = _name;
}
