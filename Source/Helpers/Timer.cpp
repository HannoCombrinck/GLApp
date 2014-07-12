#include "Timer.h"

#include <windows.h>

namespace baselib {

	Timer::Timer(const std::string& sName)
		: m_sName(sName)
	{
	}

	Timer::~Timer()
	{
	}

	__int64 Timer::getElapsedTime() const
	{
		__int64 iIntervalTime = m_iEnd - m_iStart;
		return (iIntervalTime * 1000000) / m_iFrequency;
	}

	void Timer::start()
	{
		LARGE_INTEGER iFrequency;
		LARGE_INTEGER iCount;
		QueryPerformanceFrequency(&iFrequency);
		QueryPerformanceCounter(&iCount);
		m_iStart = iCount.QuadPart;
		m_iFrequency = iFrequency.QuadPart;
	}

	void Timer::stop()
	{
		LARGE_INTEGER iCount;
		QueryPerformanceCounter(&iCount);
		m_iEnd = iCount.QuadPart;
	}

}
