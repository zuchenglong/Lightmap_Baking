#pragma once
#include <time.h>

static float m_DeltaTime = 0;
static clock_t m_PreTime = 0;
static clock_t m_CurrTime = 0;

#define LOG_DELTA_TIME 0

class Time
{
public:
	Time();
	~Time();

	static void Init();
	static void Tick();

	static float GetDeltaTime();
private:

};
