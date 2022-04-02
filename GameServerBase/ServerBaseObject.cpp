#include "pch.h"
#include "ServerBaseObject.h"
#include "ServerDebug.h"

ServerBaseObject::ServerBaseObject()
	: m_parent(nullptr)
{
	m_linkObject.resize(16);
}

ServerBaseObject::~ServerBaseObject()
{
}

ServerBaseObject::ServerBaseObject(ServerBaseObject&& _other) noexcept
	: m_parent(_other.m_parent)
{
}

bool ServerBaseObject::IsLowLevelValid()
{
	if (nullptr != this)
	{
		return true;
	}

	return false;
}

void ServerBaseObject::SetParent(ServerBaseObject* _parent)
{
	// 자기 자신을 부모로 넣을 수 없음
	if (this == _parent)
	{
		return;
	}

	// 한번에 처리
	m_parent = _parent;
}


void ServerBaseObject::SetLink(size_t _index, std::shared_ptr<ServerBaseObject> _ptr)
{
	// 넣으려는 인덱스가 벡터크기보다 큰경우 벡터 사이즈 증가
	if (_index >= m_linkObject.size())
	{
		m_linkObject.resize(_index + 1);
	}

	if (_index >= 128)
	{
		ServerDebug::AssertDebugMsg("is Big Index Index Not Over 128.");
		return;
	}

	// 자리에 이미 있는경우 
	if (nullptr != m_linkObject[_index])
	{
		ServerDebug::AssertDebugMsg("is OverLap Link Data");
		return;
	}

	// 자기 자신을 link로 넣을 수 없음
	if (this == _ptr.get())
	{
		return;
	}

	m_linkObject[_index] = _ptr;
}

const std::vector<std::shared_ptr<ServerBaseObject>>& ServerBaseObject::GetAllLink() const
{
	return m_linkObject;
}

void ServerBaseObject::ClearLinkObject()
{
	m_linkObject.clear();
}
