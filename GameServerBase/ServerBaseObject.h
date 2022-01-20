#pragma once

// �뵵 : 
// �з� :
// ÷�� :
// ���� �����ӿ�ũ���� ����� ��� Ŭ������ �θ� ������Ʈ
// ��� ������Ʈ���� ����� ����� ����
class ServerBaseObject : public std::enable_shared_from_this<ServerBaseObject>
{
private: // member var
	ServerBaseObject*				m_parent;		// �θ� ������Ʈ
	std::vector<ServerBaseObject*>	m_linkObject;	// ������Ʈ�� ����� �ٸ� ������Ʈ

public: // default
	ServerBaseObject();
	virtual ~ServerBaseObject(); // �����Լ� ���̺��� ���

	ServerBaseObject(const ServerBaseObject& _other) = delete;
	ServerBaseObject(ServerBaseObject&& _other) noexcept;

protected:
	ServerBaseObject& operator=(const ServerBaseObject& _other) = delete;
	ServerBaseObject& operator=(const ServerBaseObject&& _other) = delete;

private:

public: // member Func
	bool IsLowLevelValid();

	void SetParent(ServerBaseObject* _parent);

	// Ÿ���� �߸��Ǿ��ų� �θ�ü�� ���°�� nullptr
	template<typename ParentType>
	ParentType* GetParent() const
	{
		return dynamic_cast<ParentType*>(m_parent);
	}

	void SetLink(ServerBaseObject* _link);

	// Ÿ���� �߸��� ��� nullptr
	template<typename LinkObjectType>
	const ServerBaseObject* GetLink(UINT _idx) const
	{
		return dynamic_cast<LinkObjectType*>(m_linkObject[_idx]);
	}

	const std::vector<ServerBaseObject*>& GetAllLink() const;
};

