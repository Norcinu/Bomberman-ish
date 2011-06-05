#ifndef TIMER_H
#define TIMER_H

// maybe re-write this using boost or in some other cross-platform way.

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <Windows.h>

class Timer
{
public:
	Timer(void) { Reset(); }

	~Timer(void) {}

	void Reset()
	{
		unsigned long long freq;
		QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
		m_frequency = 1.0 / (double)freq;
		QueryPerformanceCounter((LARGE_INTEGER *) &m_baseTime);
	}

	double Seconds()
	{
		unsigned long long value;
		QueryPerformanceCounter((LARGE_INTEGER *) &value);
		return (value - m_baseTime) * m_frequency;
	}

	double Milliseconds() { return Seconds() * 1000.0; }

private:
	double m_frequency;
	unsigned long long m_baseTime;
};

#endif
