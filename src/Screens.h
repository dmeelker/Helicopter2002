#ifndef SCREENS_H
#define SCREENS_H

typedef enum Screens {
	SCREEN_MENU,
	SCREEN_GAME,
} Screens;

void screenUpdate(float frameTime);
void screenRender();
void screenSwitch(Screens screen);

#endif