#ifndef LERP_H
#define LERP_H

float lerp(float value, float min, float max)
{
	return min + value * (max - min);
}

#endif
