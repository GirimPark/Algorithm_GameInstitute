#include "Timer.h"
#include <iostream>

Timer::Timer()
{
	QueryPerformanceFrequency(&m_frequency);
}

double Timer::GetElapsedTime()
{
	double elapsedTime = (double)(m_endTime.QuadPart - m_beginTime.QuadPart) / (double)m_frequency.QuadPart;

	std::cout << "����ð� : " << elapsedTime * 1000 << "ms" << std::endl;

	return elapsedTime;
}

void Timer::Start()
{
	QueryPerformanceCounter(&m_beginTime);
}

void Timer::Stop()
{
	QueryPerformanceCounter(&m_endTime);
}
