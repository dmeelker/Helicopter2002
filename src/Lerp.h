#ifndef LERP_H
#define LERP_H

#include <stdlib.h>

typedef struct Size {
	int width;
	int height;
} Size;

float lerp(float value, float min, float max);
int random(int min, int max);
int clamp(int value, int min, int max);

#endif
