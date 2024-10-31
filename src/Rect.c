#include "Rect.h"

bool rectIntersects(const Rect a, const Rect b)
{
	return a.x < b.x + b.width &&
		a.x + a.width > b.x &&
		a.y < b.y + b.height &&
		a.y + a.height > b.y;
}
