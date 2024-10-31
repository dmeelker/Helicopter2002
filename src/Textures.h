#ifndef TEXTURES_H
#define TEXTURES_H

#include <raylib.h>

typedef struct Textures {
	Texture2D helicopter;
	Texture2D smoke;
} Textures;

extern Textures textures;

void texturesLoad();

#endif
