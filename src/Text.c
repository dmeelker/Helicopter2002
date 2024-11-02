#include "assets/Fonts.h"
#include "Lerp.h"
#include "Text.h"
#include <stdlib.h>

#define TEXT_ORANGE { { 255, 162, 0, 255 }, { 121, 56, 0, 255 }}
#define TEXT_YELLOW { { 235, 211, 32, 255 }, { 138, 138, 0, 255 }}

TextStyle TEXT_ORANGE_MEDIUM = { 12 * 4, 3, 3, TEXT_ORANGE };
TextStyle TEXT_YELLOW_LARGE = { 12 * 6, 3, 4, TEXT_YELLOW };

void renderText(const char* text, Vector2 position)
{
	DrawTextEx(fonts.large, text, (Vector2) { position.x + 2, position.y + 2 }, 30, 4, (Color) { 121, 56, 0, 255 });
	DrawTextEx(fonts.large, text, position, 30, 4, (Color) { 255, 162, 0, 255 });
}

void renderTextCentered(TextStyle* style, const char* text, Vector2 center)
{
	Vector2 size = MeasureTextEx(fonts.large, text, style->size, style->spacing);
	Vector2 location = { center.x - (size.x / 2), center.y - (size.y / 2) };

	DrawTextEx(fonts.large, text, (Vector2) { location.x + style->shadowOffset, location.y + style->shadowOffset }, style->size, style->spacing, style->colors.shadow);
	DrawTextEx(fonts.large, text, location, style->size, style->spacing, style->colors.text);
}

void renderTextCenteredWiggle(TextStyle* style, const char* text, Vector2 center)
{
	Vector2 location = { center.x + (rand() % 2) - 1, center.y + (rand() % 2) - 1 };
	renderTextCentered(style, text, wiggle(location));
}

void renderDropText(TextStyle* style, TextAnimation* animation, const char* text)
{
	if (!animation->active)
	{
		return;
	}

	float progress = (GetTime() - animation->start) / animation->duration;
	if (progress >= 1.0f)
	{
		progress = 1.0f;
	}

	progress = easeOutCubic(progress);

	Vector2 location = {
		lerp(progress, animation->startPosition.x, animation->endPosition.x),
		lerp(progress, animation->startPosition.y, animation->endPosition.y) };

	renderTextCenteredWiggle(style, text, location);
}
