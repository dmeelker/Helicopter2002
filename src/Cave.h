#ifndef CAVE_H
#define CAVE_H

#include "Constants.h"
#include "Rect.h"

#define MAX_BLOCKS 1000

typedef struct Block {
	bool used;
	Rect rect;
} Block;

void levelRender();
void levelClear();
void levelGeneratePath();
bool levelCollides(Rect rect);

#endif
