#pragma once
#include <thread>
#include <typeinfo>

#include "ServerNameBase.h"
#include "ServerDebug.h"

// �뵵 :
// �з� :
// ÷�� :
class ServerThread : public ServerNameBase
{
private:
	// thread������ ����� �޸𸮿���
	static thread_local std::string THREAD_NAME;
	static thread_local unsigned int THREAD_OREDER;
	static thread_local const std::type_info* LOCAL_DATA_TYPE;
	static thread_local std::vector<char> LOCAL_DATA;

private: // member var
	std::thread m_thread;

public: // default
	template <class _Fn, class... _Args, std::enable_if_t<!std::is_same_v<std::_Remove_cvref_t<_Fn>, std::thread>, int> = 0>
	explicit ServerThread(std::string _name, _Fn&& _Fx, _Args&&... _Ax)
	{
		m_thread = std::thread(_Fx, _Ax...);
	}

	template <class _Fn, class... _Args, std::enable_if_t<!std::is_same_v<std::_Remove_cvref_t<_Fn>, std::thread>, int> = 0>
	explicit ServerThread(_Fn&& _Fx, _Args&&... _Ax)
		: ServerNameBase("default thread")
	{
		m_thread = std::thread(_Fx, _Ax...);
	}

	~ServerThread();

	ServerThread(const ServerThread& _other) = delete;
	ServerThread(const ServerThread&& _other) noexcept;
	

protected:
	ServerThread& operator=(const ServerThread& _other) = delete;
	ServerThread& operator=(const ServerThread&& _other) = delete;

private:

public: // static
	static void SetThreadName(const std::string& _Name);
	static std::string GetName();

public: // inline
	inline std::thread::id ThreadId()
	{
		return m_thread.get_id();
	}

	inline void SetThreadOrder(unsigned int _Order)
	{
		THREAD_OREDER = _Order;
	}


public: // member Func
	void Join();


public:
	template<typename LocalDataType>
	static LocalDataType* CreateThreadLocalData()
	{
		// �̹� ��������ִ��� üũ
		if (nullptr != LOCAL_DATA_TYPE)
		{
			ServerDebug::AssertDebugMsg("Local Data Is Not Null");
			return nullptr;
		}

		LOCAL_DATA_TYPE = &typeid(LocalDataType);

		// �޸� �Ҵ�
		LOCAL_DATA.resize(sizeof(LocalDataType));

		// �ּҰ� ��ȯ
		return new (&LOCAL_DATA[0]) LocalDataType();
	}

	template<typename LocalDataType>
	static LocalDataType* GetLocalData()
	{
		// 0. �����帶�� �ٸ� �����͸� ��������.
		// 1. �ٸ� �ڷ������� �ڵ带 ġ�� ������� ���ƾ� // RTTI
		// DBConnecter�Ҵ��ߴµ�. NetworkManager�� �޶�� �ϴ� ���.
		// 2. �Ϲ����� Ŭ������ �Ҵ��� �� �ֵ��� �����ڸ� ����.
		// 3. �̷� �� �𸮾��̳� �ֱ� �޸�Ʈ����� 
		//    list���� vector�� ����� �޸𸮸� �Ҵ��ϴ°� ��õ�ǰ� �־��
		//    ���� ������ ������ �ϰ� �ʹ�
		//    for Ƚ���� ���̴°� �ƴ϶�. �޸𸮸� ����ȭ�ϸ�
		//    �ӷµ� �´�.
		// 
		// 
		// RTTI�� ���� ������ �ڷ���Ÿ�԰� �������� Ÿ���� ������ Ȯ��
		if (LOCAL_DATA_TYPE != &typeid(LocalDataType))
		{
			ServerDebug::AssertDebugMsg("Local Data Type Is Not Equal");
			return nullptr;
		}

		return (LocalDataType*)&LOCAL_DATA[0];
	}
};

