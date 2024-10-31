#include "Vector.h"

Vector vectorAdd(Vector a, Vector b)
{
	Vector result = { a.x + b.x, a.y + b.y };
	return result;
}

Vector vectorMultiply(Vector a, float scalar)
{
	Vector result = { a.x * scalar, a.y * scalar };
	return result;
}
