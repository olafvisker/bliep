#pragma once
#include <string>

enum LogLevel
{
	LOG_EMPTY,
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
};

namespace Logger
{
	extern std::string GetFilePath();
	extern void SetFilePath(const std::string& filePath);

	extern bool& LogToFile();
	extern bool& LogToConsole();

	extern void Initialize(const std::string& filePath);
	extern void Close();

	extern void Log(LogLevel logLevel, char* logline);
	extern void Log(LogLevel logLevel, const char* logline, ...);
};