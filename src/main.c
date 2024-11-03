#include "assets/Audio.h"
#include "assets/Fonts.h"
#include "Constants.h"
#include "Screens.h"
#include "Settings.h"
#include "Textures.h"
#include <raylib.h>

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Helicopter 2002");
	InitAudioDevice();
	SetTargetFPS(60);
	SetExitKey(0);

	// Load assets
	texturesLoad();
	fontsLoad();
	audioLoad();
	settingsLoad();

	SetMusicVolume(audio.music, 0.6f);

	if (settings.enableSound)
	{
		PlayMusicStream(audio.music);
	}
	screenSwitch(SCREEN_MENU);

	while (!WindowShouldClose())
	{
		UpdateMusicStream(audio.music);
		screenUpdate(GetFrameTime());
		screenRender();
	}
	CloseWindow();

	return 0;
}
