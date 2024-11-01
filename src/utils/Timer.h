#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

typedef struct Timer {
	float lastTriggerTime;
	float interval;
} Timer;

Timer timerCreate(float interval);
bool timerUpdate(Timer* timer);

#endif