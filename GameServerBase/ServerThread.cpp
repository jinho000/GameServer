#include "pch.h"
#include "ServerThread.h"

thread_local std::string ServerThread::THREAD_NAME;
thread_local unsigned int ServerThread::THREAD_OREDER;
thread_local const std::type_info* ServerThread::LOCAL_DATA_TYPE = nullptr;
thread_local std::vector<char> ServerThread::LOCAL_DATA;


ServerThread::~ServerThread()
{
}

ServerThread::ServerThread(const ServerThread&& _other) noexcept
	: ServerNameBase(_other.GetName())
{
}

void ServerThread::SetThreadName(const std::string& _Name)
{
	THREAD_NAME = _Name;

	std::wstring String;
	String.assign(_Name.begin(), _Name.end());
	HRESULT hr = SetThreadDescription(GetCurrentThread(), String.c_str());
}

std::string ServerThread::GetName()
{
	return THREAD_NAME;
}

void ServerThread::Join()
{
	m_thread.join();
}
