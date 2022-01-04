#pragma once
#include <thread>
#include "ServerNameBase.h"

// 용도 :
// 분류 :
// 첨언 :
class ServerThread : public ServerNameBase
{
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

public: // member Func
};

