#include "assets/Fonts.h"
#include "Lerp.h"
#include "Text.h"
#include <stdlib.h>

#define TEXT_ORANGE { { 255, 162, 0, 255 }, { 121, 56, 0, 255 }}
#define TEXT_DARK_ORANGE { { 195, 113, 0, 255 }, { 121, 56, 0, 255 }}
#define TEXT_YELLOW { { 235, 211, 32, 255 }, { 138, 138, 0, 255 }}

TextStyle TEXT_ORANGE_SMALL = { 12 * 2, 2, 1, TEXT_DARK_ORANGE };
TextStyle TEXT_ORANGE_MEDIUM = { 12 * 4, 3, 3, TEXT_ORANGE };
TextStyle TEXT_ORANGE_LARGE = { 12 * 6, 3, 4, TEXT_ORANGE };
TextStyle TEXT_YELLOW_SMALL = { 12 * 2, 3, 3, TEXT_YELLOW };
TextStyle TEXT_YELLOW_MEDIUM = { 12 * 4, 3, 3, TEXT_YELLOW };
TextStyle TEXT_YELLOW_LARGE = { 12 * 6, 3, 4, TEXT_YELLOW };

void renderText(TextStyle* style, const char* text, Vector2 location)
{
	DrawTextEx(fonts.large, text, (Vector2) { location.x + style->shadowOffset, location.y + style->shadowOffset }, (float)style->size, (float)style->spacing, style->colors.shadow);
	DrawTextEx(fonts.large, text, location, (float)style->size, (float)style->spacing, style->colors.text);
}

void renderTextCentered(TextStyle* style, const char* text, Vector2 center)
{
	Vector2 size = MeasureTextEx(fonts.large, text, (float)style->size, (float)style->spacing);
	Vector2 location = { center.x - (size.x / 2), center.y - (size.y / 2) };

	DrawTextEx(fonts.large, text, (Vector2) { location.x + style->shadowOffset, location.y + style->shadowOffset }, (float)style->size, (float)style->spacing, style->colors.shadow);
	DrawTextEx(fonts.large, text, location, (float)style->size, (float)style->spacing, style->colors.text);
}

void renderTextCenteredWiggle(TextStyle* style, const char* text, Vector2 center)
{
	Vector2 location = { center.x + (rand() % 2) - 1, center.y + (rand() % 2) - 1 };
	renderTextCentered(style, text, wiggle(location));
}