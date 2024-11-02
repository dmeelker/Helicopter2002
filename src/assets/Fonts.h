#ifndef FONTS_H
#define FONTS_H

#include <raylib.h>

typedef struct Fonts {
	Font large;
} Fonts;

extern Fonts fonts;

void fontsLoad();

#endif // FONTS_H
