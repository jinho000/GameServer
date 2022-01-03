#include "pch.h"
#include "ServerBaseObject.h"

ServerBaseObject::ServerBaseObject()
	: m_parent(nullptr)
{
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
	m_parent->SetLink(this);
}

void ServerBaseObject::SetLink(ServerBaseObject* _link)
{
	// 자기 자신을 link로 넣을 수 없음
	if (this == _link)
	{
		return;
	}

	// 중복처리(같은 객체를 두번넣는 경우 방지)
	for (int i = 0; i < m_linkObject.size(); ++i)
	{
		if (this == m_linkObject[i])
		{
			return;
		}
	}

	// 한번에 처리
	m_linkObject.push_back(_link);
	_link->SetParent(this);
}

const std::vector<ServerBaseObject*>& ServerBaseObject::GetAllLink() const
{
	return m_linkObject;
}
