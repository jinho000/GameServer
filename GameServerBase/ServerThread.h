#pragma once
#include <thread>
#include <typeinfo>

#include "ServerNameBase.h"
#include "ServerDebug.h"

// 용도 :
// 분류 :
// 첨언 :
class ServerThread : public ServerNameBase
{
private:
	// thread에서만 사용할 메모리영역
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
		// 이미 만들어져있는지 체크
		if (nullptr != LOCAL_DATA_TYPE)
		{
			ServerDebug::AssertDebugMsg("Local Data Is Not Null");
			return nullptr;
		}

		LOCAL_DATA_TYPE = &typeid(LocalDataType);

		// 메모리 할당
		LOCAL_DATA.resize(sizeof(LocalDataType));

		// 주소값 반환
		return new (&LOCAL_DATA[0]) LocalDataType();
	}

	template<typename LocalDataType>
	static LocalDataType* GetLocalData()
	{
		// 0. 쓰레드마다 다른 데이터를 가져야해.
		// 1. 다른 자료형으로 코드를 치는 사람들을 막아야 // RTTI
		// DBConnecter할당했는데. NetworkManager를 달라고 하는 사람.
		// 2. 일반적인 클래스도 할당할 수 있도록 생성자를 지연.
		// 3. 이론 왜 언리얼이나 최근 메모리트랜드는 
		//    list보다 vector에 가까운 메모리를 할당하는게 추천되고 있어요
		//    내가 뭔가를 빠르게 하고 싶다
		//    for 횟수를 줄이는게 아니라. 메모리를 최적화하면
		//    속력도 는다.
		// 
		// 
		// RTTI를 통해 생성한 자료형타입과 가져오는 타입이 같은지 확인
		if (LOCAL_DATA_TYPE != &typeid(LocalDataType))
		{
			ServerDebug::AssertDebugMsg("Local Data Type Is Not Equal");
			return nullptr;
		}

		return (LocalDataType*)&LOCAL_DATA[0];
	}
};

