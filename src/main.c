#include "assets/Fonts.h"
#include "Constants.h"
#include "Screens.h"
#include <raylib.h>

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Elicopter");
	SetTargetFPS(60);

	texturesLoad();
	fontsLoad();

	screenSwitch(SCREEN_MENU);

	while (!WindowShouldClose())
	{
		screenUpdate(GetFrameTime());
		screenRender();
	}
	CloseWindow();

	return 0;
}
