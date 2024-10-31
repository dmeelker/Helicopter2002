#ifndef CAVE_H
#define CAVE_H

#include "Constants.h"
#include "Rect.h"


#define BLOCK_WIDTH 50

typedef struct Block {
	bool used;
	Rect rect;
} Block;

void levelRender();
void levelReset();
//void levelGeneratePath();
bool levelCollides(Rect rect);
void levelUpdate(int xOffset);

#endif
