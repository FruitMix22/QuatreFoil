#pragma once
#include <vector>
#include <string>

class Console
{
public:
	static void Log(const std::string& logMessage);
	static void Clear();
	static const std::vector<std::string>& GetLogs();

private:
	static std::vector<std::string> m_logs;
};