#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <deque>

#include "Logger.h"

std::ofstream m_stream;
std::string m_filePath = "Dump.log";

bool m_logToFile = true;
bool m_logToConsole = true;

bool firstLog = true;
std::deque<std::string> m_prevMessages;
LogLevel prevLogLevel = LogLevel::LOG_EMPTY;
const unsigned int historyStorageCount = 50;

const std::string m_logLevelStrings[] =
{ "          ",
  "[INFO]    ",
  "[DEBUG]   ",
  "[WARNING] ",
  "[ERROR]   " };

std::string Logger::GetFilePath() 
{ 
	return m_filePath; 
}

void Logger::SetFilePath(const std::string& filePath)
{
	Close();
	Initialize(filePath);
}

bool& Logger::LogToFile()		{ return m_logToFile; }
bool& Logger::LogToConsole()	{ return m_logToConsole; }

void Logger::Initialize(const std::string& filePath)
{
	m_stream.open(filePath);
	m_filePath = filePath;
}

void Logger::Close()
{
	m_stream.close();
}

void Logger::Log(LogLevel logLevel, char* logline)
{
	if (firstLog)
	{
		prevLogLevel = logLevel;
		firstLog = false;
	}

	if (std::find(m_prevMessages.begin(), m_prevMessages.end(), logline) == m_prevMessages.end())
	{
		if (m_logToFile)
		{
			if (prevLogLevel != logLevel)
				m_stream << std::endl;

			m_stream << m_logLevelStrings[logLevel] << logline << std::endl;
		}

		if (m_logToConsole)
		{
			if (prevLogLevel != logLevel)
				std::cout << std::endl;

			std::cout << m_logLevelStrings[logLevel] << logline << std::endl;
		}

		if (logLevel != LogLevel::LOG_DEBUG)
			m_prevMessages.push_back(logline);

		prevLogLevel = logLevel;

		if (m_prevMessages.size() > historyStorageCount)
			m_prevMessages.pop_front();
	}
}

void Logger::Log(LogLevel logLevel, const char* logline, ...)
{
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf_s(cbuffer, 1024, logline, argList);
	va_end(argList);
	Log(logLevel, cbuffer);
}