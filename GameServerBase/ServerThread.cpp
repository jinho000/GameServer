#include "pch.h"
#include "ServerThread.h"

ServerThread::~ServerThread()
{
}

ServerThread::ServerThread(const ServerThread&& _other) noexcept
	: ServerNameBase(_other.GetName())
{
}
