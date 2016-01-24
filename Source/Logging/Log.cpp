#include "Log.h"
#include <time.h>

namespace baselib {

	LOG_LEVEL Logger::m_LogLevel = LOGLEVEL_INFO;
	bool Logger::m_bAddLogLevel = true;
	bool Logger::m_bAddTimeStamp = false;

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	   m_OutStream << std::endl;
	   std::cout << m_OutStream.str();
	}

	namespace
	{
		std::string levelToString(LOG_LEVEL level)
		{
			std::string logLevelStr = "";
			switch (level)
			{
			case LOGLEVEL_ERROR: logLevelStr = "     Error"; break;
			case LOGLEVEL_WARNING: logLevelStr = "   Warning"; break;
			case LOGLEVEL_INFO: logLevelStr = "      Info"; break;
			case LOGLEVEL_DEBUG_INFO: logLevelStr = "Debug Info"; break;
			case LOGLEVEL_VERBOSE: logLevelStr = "   Verbose"; break;
			default: assert(false); 
			}
			return logLevelStr;
		}

		// From http://msdn.microsoft.com/en-us/library/a442x3ye.aspx
		static const std::string currentDateTime() {
			struct tm newtime;
			char am_pm[] = "AM";
			__time64_t long_time;
			char timebuf[26];
			errno_t err;

			// Get time as 64-bit integer.
			_time64( &long_time ); 
			// Convert to local time.
			err = _localtime64_s( &newtime, &long_time ); 
			if (err)
			{
				printf("Invalid argument to _localtime64_s.");
				exit(1);
			}
			if( newtime.tm_hour > 12 )        // Set up extension. 
					strcpy_s( am_pm, sizeof(am_pm), "PM" );
			if( newtime.tm_hour > 12 )        // Convert from 24-hour 
					newtime.tm_hour -= 12;    // to 12-hour clock. 
			if( newtime.tm_hour == 0 )        // Set hour to 12 if midnight.
					newtime.tm_hour = 12;

			// Convert to an ASCII representation. 
			err = asctime_s(timebuf, 26, &newtime);
			if (err)
			{
			   printf("Invalid argument to asctime_s.");
			   exit(1);
			}
			timebuf[19] = '\0';
			return std::string(timebuf) + " " + std::string(am_pm);
		}
	}

	std::ostringstream& Logger::getStream(LOG_LEVEL level)
	{
		if (getAddTimeStamp())
		{
			m_OutStream << "[" << currentDateTime();

			if (getAddLogLevel())
				m_OutStream << " - " << levelToString(level) << "]\t";
			else
				m_OutStream << "]\t";
		}
		else if (getAddLogLevel())
		{
			m_OutStream << "[" << levelToString(level) << "]\t";
		}
		
		return m_OutStream;
	}

}