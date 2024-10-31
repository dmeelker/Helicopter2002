#ifndef RECT_H
#define RECT_H

#include <stdbool.h>

typedef struct Rect {
	float x;
	float y;
	float width;
	float height;
} Rect;

bool rectIntersects(const Rect a, const Rect b);

#endif // !RECT_H
