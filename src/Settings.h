#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

typedef struct Settings {
	bool enableSound;
} Settings;

extern Settings settings;

void settingsLoad();

#endif