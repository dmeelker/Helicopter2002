#include "Audio.h"

Audio audio;

void audioLoad()
{
	audio.music = LoadMusicStream("assets/audio/music.mp3");
	audio.music.looping = true;

	audio.heli = LoadSound("assets/audio/heli_fast.mp3");
	audio.crash = LoadSound("assets/audio/crash.mp3");
}
