#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
	float x;
	float y;
} Vector;

Vector vectorAdd(Vector a, Vector b);
Vector vectorMultiply(Vector a, float scalar);

#endif // !VECTOR_H