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

float easeOutCubic(float x)
{
	return 1.0f - pow(1.0f - x, 3.0f);
}

float easeOutBounce(float x)
{
	const n1 = 7.5625;
	const d1 = 2.75;

	if (x < 1 / d1)
	{
		return n1 * x * x;
	}
	else if (x < 2 / d1)
	{
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1)
	{
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else
	{
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

Vector2 wiggle(Vector2 vector)
{
	return (Vector2) { vector.x + (rand() % 2) - 1, vector.y + (rand() % 2) - 1 };
}
