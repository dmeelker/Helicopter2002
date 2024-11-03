#include "Timer.h"
#include <raylib.h>

Timer timerCreate(float interval)
{
	return (Timer) { (float)GetTime(), interval };
}

bool timerUpdate(Timer* timer)
{
	float time = (float)GetTime();
	if (time - timer->lastTriggerTime >= timer->interval)
	{
		timer->lastTriggerTime = time;
		return true;
	}
	return false;
}
