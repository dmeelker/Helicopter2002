#include "Constants.h"
#include "MenuScreen.h"
#include "Screens.h"
#include "Text.h"
#include "Textures.h"
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
	DrawTexture(textures.titleScreen, 0, 0, WHITE);

	renderTextCentered(&TEXT_ORANGE_LARGE, "Helicopter 2002", (Vector2) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	if ((int)(GetTime() * 1000.0f) % 2000 > 1000)
	{
		renderTextCentered(&TEXT_ORANGE_MEDIUM, "Click to play", (Vector2) { SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 50 });
	}

	renderText(&TEXT_ORANGE_SMALL, "A DENSPEL GAME", (Vector2) { SCREEN_WIDTH - 230, 10 });

	EndDrawing();
}
