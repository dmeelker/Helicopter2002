#include "Settings.h"
#include <stdio.h>

Settings settings = { .enableSound = true };

void settingsLoad()
{
	FILE* file = fopen("settings.txt", "r");
	if (file == NULL)
	{
		return;
	}

	unsigned char buffer[32];
	size_t read = fread(buffer, 1, sizeof(buffer), file);

	if (read > 0)
	{
		buffer[read] = '\0';

		if (strcmp(buffer, "music=true") == 0)
		{
			settings.enableSound = true;
		}
		else
		{
			settings.enableSound = false;
		}
	}

	fclose(file);
}
