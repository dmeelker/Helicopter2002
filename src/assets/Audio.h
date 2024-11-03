#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

typedef struct Audio {
	Music music;
	Sound heli;
	Sound crash;
} Audio;

extern Audio audio;

void audioLoad();

#endif
