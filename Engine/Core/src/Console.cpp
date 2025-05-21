#include "Core/include/Console.hpp"

void Console::Log(const std::string& logMessage)
{
	m_logs.push_back(logMessage);
}

void Console::Clear()
{
	m_logs.clear();
}

const std::vector<std::string>& Console::GetLogs()
{
	return m_logs;
}

std::vector<std::string> Console::m_logs;



