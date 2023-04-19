#include "Time.h"
#include <iostream>
#include <string>
	
Time::Time()
{

}

void Time::Init()
{

}

void Time::Tick()
{

	m_CurrTime = clock();


	m_DeltaTime = (m_CurrTime - m_PreTime) * 0.001f;

#if LOG_DELTA_TIME
	std::cout << "DeltaTime=" << std::to_string(m_DeltaTime) << "CurrTime=" << std::to_string(m_CurrTime) << "PreTime=" << std::to_string(m_PreTime) << std::endl;
#endif // LOG_DELTA_TIME

	m_PreTime = m_CurrTime;

}

float Time::GetDeltaTime()
{
	return m_DeltaTime;
}

Time::~Time()
{

}