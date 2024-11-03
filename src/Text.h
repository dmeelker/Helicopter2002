#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
#include <stdbool.h>

typedef struct TextColors {
	Color text;
	Color shadow;
} TextColors;

typedef struct TextStyle {
	int size;
	int spacing;
	int shadowOffset;
	TextColors colors;
} TextStyle;

extern TextStyle TEXT_ORANGE_MEDIUM;
extern TextStyle TEXT_ORANGE_SMALL;
extern TextStyle TEXT_ORANGE_LARGE;
extern TextStyle TEXT_YELLOW_SMALL;
extern TextStyle TEXT_YELLOW_MEDIUM;
extern TextStyle TEXT_YELLOW_LARGE;

void renderText(TextStyle* style, const char* text, Vector2 location);
void renderTextCentered(TextStyle* style, const char* text, Vector2 center);
void renderTextCenteredWiggle(TextStyle* style, const char* text, Vector2 center);

#endif // TEXT_H
