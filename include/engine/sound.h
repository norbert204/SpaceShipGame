#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

int sound_init();
void sound_playMusic(const char *file);
void sound_stop();

#endif