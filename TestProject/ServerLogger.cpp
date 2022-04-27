#include "ServerLogger.h"
#include <iostream>

ServerLogger::ServerLogger()
{
	m_logQueue.Initialize(1, "LogThread");

}

ServerLogger::~ServerLogger()
{
	m_logQueue.Destroy();
}

void ServerLogger::LogWork(const std::string& _log)
{
	std::cout << _log << std::endl;
}

void ServerLogger::Log(const std::string& _log)
{
	m_logWork = std::bind(&ServerLogger::LogWork, this, _log);
	m_logQueue.Enqueue(m_logWork);
}
