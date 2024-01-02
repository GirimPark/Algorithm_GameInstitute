#pragma once

#include <Windows.h>
class Timer
{
private:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_beginTime;
	LARGE_INTEGER m_endTime;

public:
	Timer();

public:
	double GetElapsedTime();

public:
	void Start();
	void Stop();
};

