#include "Constants.h"
#include "MenuScreen.h"
#include "Screens.h"
#include <raylib.h>

void menuUpdate(float frameTime)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		screenSwitch(SCREEN_GAME);
	}
}

void menuRender()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	int width = MeasureText("Elicopter", 80);
	DrawText("Elicopter", SCREEN_WIDTH / 2 - width / 2, SCREEN_HEIGHT / 2 - 80, 80, BLACK);

	if ((int)(GetTime() * 1000.0f) % 2000 > 1000)
	{
		int subWidth = MeasureText("Click to play", 40);
		DrawText("Click to play", SCREEN_WIDTH / 2 - subWidth / 2, SCREEN_HEIGHT / 2, 40, BLACK);
	}

	EndDrawing();
}
