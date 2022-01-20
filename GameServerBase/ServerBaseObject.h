#pragma once

// 용도 : 
// 분류 :
// 첨언 :
// 서버 프레임워크에서 사용할 모든 클래스의 부모 오브젝트
// 모든 오브젝트에서 사용할 기능을 관리
class ServerBaseObject : public std::enable_shared_from_this<ServerBaseObject>
{
private: // member var
	ServerBaseObject*				m_parent;		// 부모 오브젝트
	std::vector<ServerBaseObject*>	m_linkObject;	// 오브젝트에 연결된 다른 오브젝트

public: // default
	ServerBaseObject();
	virtual ~ServerBaseObject(); // 가상함수 테이블을 사용

	ServerBaseObject(const ServerBaseObject& _other) = delete;
	ServerBaseObject(ServerBaseObject&& _other) noexcept;

protected:
	ServerBaseObject& operator=(const ServerBaseObject& _other) = delete;
	ServerBaseObject& operator=(const ServerBaseObject&& _other) = delete;

private:

public: // member Func
	bool IsLowLevelValid();

	void SetParent(ServerBaseObject* _parent);

	// 타입이 잘못되었거나 부모객체가 없는경우 nullptr
	template<typename ParentType>
	ParentType* GetParent() const
	{
		return dynamic_cast<ParentType*>(m_parent);
	}

	void SetLink(ServerBaseObject* _link);

	// 타입이 잘못된 경우 nullptr
	template<typename LinkObjectType>
	const ServerBaseObject* GetLink(UINT _idx) const
	{
		return dynamic_cast<LinkObjectType*>(m_linkObject[_idx]);
	}

	const std::vector<ServerBaseObject*>& GetAllLink() const;
};

