#include "Textures.h"

Textures textures;

void texturesLoad()
{
	textures.titleScreen = LoadTexture("assets/gfx/titlescreen.png");
	textures.helicopter = LoadTexture("assets/gfx/helicopter.png");
	textures.smoke = LoadTexture("assets/gfx/smoke.png");
}
