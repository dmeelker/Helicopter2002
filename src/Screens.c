#include "Game.h"
#include "MenuScreen.h"
#include "Screens.h"

Screens activeScreen = SCREEN_GAME;

void screenUpdate(float frameTime)
{
	switch (activeScreen)
	{
		case SCREEN_MENU:
			menuUpdate(frameTime);
			break;
		case SCREEN_GAME:
			gameUpdate(frameTime);
			break;
	}
}

void screenRender()
{
	switch (activeScreen)
	{
		case SCREEN_MENU:
			menuRender();
			break;
		case SCREEN_GAME:
			gameRender();
			break;
	}
}

void screenSwitch(Screens screen)
{
	activeScreen = screen;
	switch (activeScreen)
	{
		case SCREEN_MENU:
			break;
		case SCREEN_GAME:
			gameInitialize();
			break;
	}
}
