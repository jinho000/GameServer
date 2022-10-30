#include "pch.h"
#include "ServerThread.h"

//thread_local std::string ServerThread::THREAD_NAME;
thread_local unsigned int ServerThread::THREAD_OREDER;
thread_local const std::type_info* ServerThread::LOCAL_DATA_TYPE = nullptr;
//thread_local std::vector<char> ServerThread::LOCAL_DATA;
thread_local void* ServerThread::LOCAL_DATA = nullptr;
thread_local ServerTime ServerThread::Timer;

ServerThread::ServerThread()
	: ServerNameBase("")
{
}

ServerThread::~ServerThread()
{
}

ServerThread::ServerThread(const ServerThread&& _other) noexcept
	: ServerNameBase(_other.GetName())
{
}

void ServerThread::SetThreadName(const std::string& _Name)
{
	//THREAD_NAME.resize(100);
	//THREAD_NAME = _Name;

	//std::wstring String;
	//String.assign(_Name.begin(), _Name.end());
	//HRESULT hr = SetThreadDescription(GetCurrentThread(), String.c_str());
	//if (FAILED(hr))
	//{
	//	std::cout << "Set Thread Name Fail\n";
	//}
}


void ServerThread::Join()
{
	m_thread.join();
}
