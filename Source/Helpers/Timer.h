#pragma once

#include <string>

namespace baselib
{
	/*! brief Timer object that uses high resolution timestamps to measure time intervals.
	 *
	 */
	class Timer
	{
	public:
		//! Constructor.
		Timer(const std::string& sName);
		//! Destructor.
		~Timer();
	
		//! Get timer name.
		std::string getName() const { return m_sName; }
		//! Get the elapsed time of the last measured interval in microseconds.
		__int64 getElapsedTime() const;
		//! Start measuring a time interval.
		void start();
		//! Stop the current time interval being measured.
		void stop();
	
	private:
		std::string m_sName;	//!< Name of the timer object.
		__int64 m_iStart;		//!< Time stamp of the beginning of an interval in microseconds.
		__int64 m_iEnd;			//!< Time stamp of the end of an interval in microseconds.
		__int64 m_iFrequency;	//!< The frequency of the performance counter - used to calculate elapsed time.
	
	};
}
