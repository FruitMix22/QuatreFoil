#pragma once
#include <vector>
#include <string>

class Console
{
public:
	// Adds a new log to the container.
	static void Log(const std::string& logMessage);
	// Clears all logs from the container.
	static void Clear();
	// Returns a constant reference to the logs.
	static const std::vector<std::string>& GetLogs();

private:
	static std::vector<std::string> m_logs; // Container for logs.
};