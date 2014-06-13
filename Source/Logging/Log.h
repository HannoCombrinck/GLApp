#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <assert.h>

namespace baselib
{
	enum LOG_LEVEL
	{
		LOGLEVEL_NONE,
		LOGLEVEL_ERROR,
		LOGLEVEL_WARNING,
		LOGLEVEL_INFO,
		LOGLEVEL_DEBUG_INFO,
		LOGLEVEL_VERBOSE
	};

	class Logger
	{
	public:
		Logger();
		~Logger();
		
		std::ostringstream& GetStream(LOG_LEVEL level);

		static void SetLogLevel(LOG_LEVEL eLevel) { m_LogLevel = eLevel; }
		static LOG_LEVEL GetLogLevel() { return m_LogLevel; }
		
		static void SetAddTimeStamp(bool b) { m_bAddTimeStamp = b; }
		static bool GetAddTimeStamp() { return m_bAddTimeStamp; }

		static void SetAddLogLevel(bool b) { m_bAddLogLevel = b; }
		static bool GetAddLogLevel() { return m_bAddLogLevel; }

	private:
		std::ostringstream m_OutStream;

		static LOG_LEVEL m_LogLevel;
		static bool m_bAddTimeStamp;
		static bool m_bAddLogLevel;
	};

	#define LOG_ERROR \
		if (Logger::GetLogLevel() < LOGLEVEL_ERROR) ;\
		else Logger().GetStream(LOGLEVEL_ERROR) 

	#define LOG_WARNING \
		if (Logger::GetLogLevel() < LOGLEVEL_WARNING) ;\
		else Logger().GetStream(LOGLEVEL_WARNING) 

	#define LOG_INFO \
		if (Logger::GetLogLevel() < LOGLEVEL_INFO) ;\
		else Logger().GetStream(LOGLEVEL_INFO) 

	#define LOG_DEBUG \
		if (Logger::GetLogLevel() < LOGLEVEL_DEBUG_INFO) ;\
		else Logger().GetStream(LOGLEVEL_DEBUG_INFO)

	#define LOG_VERBOSE \
	if (Logger::GetLogLevel() < LOGLEVEL_VERBOSE) ;\
		else Logger().GetStream(LOGLEVEL_VERBOSE)
}
