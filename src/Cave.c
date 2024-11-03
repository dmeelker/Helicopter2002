#include "Cave.h"
#include "Constants.h"
#include "Lerp.h"
#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

#define MAX_BLOCKS 128
#define OBSTACLE_HEIGHT 150
#define MIN_GAP_SIZE 120
#define BLOCK_WIDTH 50

typedef struct CaveOpening {
	int x;
	int y;
	int height;
} CaveOpening;

Block blocks[MAX_BLOCKS];
CaveOpening previousOpening = { 0, (SCREEN_HEIGHT / 2) - 250, 500 };
CaveOpening nextOpening = { 100, (SCREEN_HEIGHT / 2) - 150, 300 };
int lastObstacleX = 0;

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
	assert(false);
	return NULL;
}

void levelRender()
{
	static Color shadowColor = { 0, 0, 0, 80 };
	const int shadowOffset = 5;

	// Draw shadows
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (blocks[i].used)
		{
			if (blocks[i].rect.y == 0)
			{
				// Top block
				DrawRectangle((int)blocks[i].rect.x, (int)blocks[i].rect.y + shadowOffset, (int)blocks[i].rect.width, (int)blocks[i].rect.height, shadowColor);
			}
			else if (blocks[i].rect.y + blocks[i].rect.height >= SCREEN_HEIGHT)
			{
				// Bottom block
				DrawRectangle((int)blocks[i].rect.x, (int)blocks[i].rect.y - shadowOffset, (int)blocks[i].rect.width, (int)blocks[i].rect.height, shadowColor);
			}
			else
			{
				// Floating block
				DrawRectangle((int)blocks[i].rect.x + shadowOffset, (int)blocks[i].rect.y + shadowOffset, (int)blocks[i].rect.width, (int)blocks[i].rect.height, shadowColor);
			}
		}
	}

	// Draw blocks
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (blocks[i].used)
		{
			DrawRectangle((int)blocks[i].rect.x, (int)blocks[i].rect.y, (int)blocks[i].rect.width, (int)blocks[i].rect.height, (Color) { 65, 146, 195, 255 });
		}
	}
}

static void createNextOpening(int xOffset)
{
	static const int maxDifficultyDistance = 50000;
	previousOpening = nextOpening;

	while (true)
	{
		float difficultyFactor = clamp(xOffset, 0, maxDifficultyDistance) / (float)maxDifficultyDistance;

		int minLength = (int)lerp(difficultyFactor, 15, 5);
		int maxLength = (int)lerp(difficultyFactor, 20, 8);
		int sectionLength = random(minLength, maxLength) * BLOCK_WIDTH;

		int minHeight = (int)lerp(difficultyFactor, 400, OBSTACLE_HEIGHT + MIN_GAP_SIZE + 20);
		int maxHeight = (int)lerp(difficultyFactor, 500, 400);
		int nextHeight = random(minHeight, maxHeight);

		int minYOffset = (int)lerp(difficultyFactor, -100, -200);
		int maxYOffset = (int)lerp(difficultyFactor, 100, 200);
		int y = clamp(previousOpening.y + random(minYOffset, maxYOffset), 50, SCREEN_HEIGHT - 50 - nextHeight);

		if (abs(y - previousOpening.y) < 50 || abs((y + nextHeight) - (previousOpening.y + previousOpening.height)) < 50)
		{
			continue;
		}

		nextOpening = (CaveOpening){ nextOpening.x + sectionLength,  y, nextHeight };
		break;
	}
}

static int getLargestGap(int obstacleY, int obstacleHeight, int gapY, int gapHeight)
{
	return max(obstacleY - gapY, (gapY + gapHeight) - (obstacleY + obstacleHeight));
}

static void generateBlocksToNextOpening()
{
	const int length = ((nextOpening.x - previousOpening.x) / BLOCK_WIDTH);
	int x = previousOpening.x + BLOCK_WIDTH;

	for (int step = 0; step < length; step++)
	{
		float progress = step / (float)length;

		int height = (int)lerp(progress, (float)previousOpening.height, (float)nextOpening.height);
		int y = (int)lerp(progress, (float)previousOpening.y, (float)nextOpening.y);

		Rect topBlock = { (float)x, 0, BLOCK_WIDTH, (float)y };
		Rect bottomBlock = { (float)x, (float)y + height, BLOCK_WIDTH, (float)SCREEN_HEIGHT - y - height };
		allocateBlock(topBlock);
		allocateBlock(bottomBlock);

		if (x - lastObstacleX > 500)
		{
			while (true)
			{
				int minY = y + 10;
				int maxY = y + height - OBSTACLE_HEIGHT - 10;
				int obstacleY = random(minY, maxY);
				int largestGap = getLargestGap(obstacleY, OBSTACLE_HEIGHT, y, height);

				if (largestGap >= MIN_GAP_SIZE)
				{
					allocateBlock((Rect) { (float)x, (float)obstacleY, BLOCK_WIDTH, OBSTACLE_HEIGHT });
					lastObstacleX = x;
					break;
				}
			}
		}

		x += BLOCK_WIDTH;
	}
}

void levelReset()
{
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		blocks[i].used = false;
	}

	previousOpening = (CaveOpening){ 0, (SCREEN_HEIGHT / 2) - 250, 500 };
	nextOpening = (CaveOpening){ SCREEN_WIDTH + BLOCK_WIDTH, (SCREEN_HEIGHT / 2) - 250, 500 };
	lastObstacleX = SCREEN_WIDTH;

	generateBlocksToNextOpening();
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

void levelUpdate(int xOffset)
{
	// Remove blocks that are off screen
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		if (blocks[i].used && blocks[i].rect.x + blocks[i].rect.width < xOffset)
		{
			blocks[i].used = false;
		}
	}

	if (nextOpening.x < xOffset + SCREEN_WIDTH)
	{
		createNextOpening(xOffset);
		generateBlocksToNextOpening();
	}
}

