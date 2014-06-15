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
		
		std::ostringstream& getStream(LOG_LEVEL level);

		static void setLogLevel(LOG_LEVEL eLevel) { m_LogLevel = eLevel; }
		static LOG_LEVEL getLogLevel() { return m_LogLevel; }
		
		static void setAddTimeStamp(bool b) { m_bAddTimeStamp = b; }
		static bool getAddTimeStamp() { return m_bAddTimeStamp; }

		static void setAddLogLevel(bool b) { m_bAddLogLevel = b; }
		static bool getAddLogLevel() { return m_bAddLogLevel; }

	private:
		std::ostringstream m_OutStream;

		static LOG_LEVEL m_LogLevel;
		static bool m_bAddTimeStamp;
		static bool m_bAddLogLevel;
	};

	#define LOG_ERROR \
		if (Logger::getLogLevel() < LOGLEVEL_ERROR) ;\
		else Logger().getStream(LOGLEVEL_ERROR) 

	#define LOG_WARNING \
		if (Logger::getLogLevel() < LOGLEVEL_WARNING) ;\
		else Logger().getStream(LOGLEVEL_WARNING) 

	#define LOG_INFO \
		if (Logger::getLogLevel() < LOGLEVEL_INFO) ;\
		else Logger().getStream(LOGLEVEL_INFO) 

	#define LOG_DEBUG \
		if (Logger::getLogLevel() < LOGLEVEL_DEBUG_INFO) ;\
		else Logger().getStream(LOGLEVEL_DEBUG_INFO)

	#define LOG_VERBOSE \
	if (Logger::getLogLevel() < LOGLEVEL_VERBOSE) ;\
		else Logger().getStream(LOGLEVEL_VERBOSE)
}
