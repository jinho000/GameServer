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
	// �ڱ� �ڽ��� �θ�� ���� �� ����
	if (this == _parent)
	{
		return;
	}

	// �ѹ��� ó��
	m_parent = _parent;
	m_parent->SetLink(this);
}

void ServerBaseObject::SetLink(ServerBaseObject* _link)
{
	// �ڱ� �ڽ��� link�� ���� �� ����
	if (this == _link)
	{
		return;
	}

	// �ߺ�ó��(���� ��ü�� �ι��ִ� ��� ����)
	for (int i = 0; i < m_linkObject.size(); ++i)
	{
		if (this == m_linkObject[i])
		{
			return;
		}
	}

	// �ѹ��� ó��
	m_linkObject.push_back(_link);
	_link->SetParent(this);
}

const std::vector<ServerBaseObject*>& ServerBaseObject::GetAllLink() const
{
	return m_linkObject;
}
