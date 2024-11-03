#include "Lerp.h"
#include <math.h>
#include <stdlib.h>

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

float minf(float x, float y)
{
	return x < y ? x : y;
}

double mind(double x, double y)
{
	return x < y ? x : y;
}

float easeOutCubic(float x)
{
	return 1.0f - (float)pow(1.0f - x, 3.0f);
}

Vector2 wiggle(Vector2 vector)
{
	return (Vector2) { vector.x + (rand() % 2) - 1, vector.y + (rand() % 2) - 1 };
}
