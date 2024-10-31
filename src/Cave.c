#include "Cave.h"
#include "Lerp.h"
#include <raylib.h>

Block blocks[MAX_BLOCKS];

static Block* allocateBlock(Rect rect)
{
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (!blocks[i].used)
		{
			blocks[i].used = true;
			blocks[i].rect = rect;
			return &blocks[i];
		}
	}
	return NULL;
}

void levelRender()
{
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (blocks[i].used)
		{
			DrawRectangle(blocks[i].rect.x, blocks[i].rect.y, blocks[i].rect.width, blocks[i].rect.height, BLUE);
		}
	}
}

void levelClear()
{
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		blocks[i].used = false;
	}
}

void levelGeneratePath()
{
	const int width = 10;

	for (int i = 0; i < 500; i++)
	{
		int height = lerp(i / 500.0f, 500, 150);
		int y = (SCREEN_HEIGHT / 2) - (height / 2);

		allocateBlock((Rect) { i* width, 0, width, y });
		allocateBlock((Rect) { i* width, y + height, width, SCREEN_HEIGHT - y - height });
	}
}

bool levelCollides(Rect rect)
{
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (blocks[i].used && rectIntersects(blocks[i].rect, rect))
		{
			return true;
		}
	}

	return false;
}
