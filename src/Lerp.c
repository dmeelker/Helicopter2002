#include "Lerp.h"

float lerp(float value, float min, float max)
{
	return min + value * (max - min);
}

int random(int min, int max)
{
	return min + rand() % (max - min);
}

int clamp(int value, int min, int max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
