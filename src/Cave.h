#ifndef CAVE_H
#define CAVE_H

#include "Rect.h"

typedef struct Block {
	bool used;
	Rect rect;
} Block;

void levelRender();
void levelReset();
bool levelCollides(Rect rect);
void levelUpdate(int xOffset);

#endif
