#ifndef LERP_H
#define LERP_H

#define CENTER(outer, inner) (((outer) / 2) - ((inner) / 2))

typedef struct Size {
	int width;
	int height;
} Size;

float lerp(float value, float min, float max);
int random(int min, int max);
int clamp(int value, int min, int max);

#endif
