#include "engine/sound.h"

static Mix_Music *music;

int sound_init()
{
    if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
    {
        fprintf(stderr, "[Engine] SDL_mixer couldn't initialize: %s\n", SDL_GetError());
        return 0;
    }
    if (!Mix_Init(MIX_INIT_OGG)) 
    {
        fprintf(stderr, "[Engine] SDL_mixer OGG support couldn't initialize: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void sound_playMusic(const char *file) 
{
    music = Mix_LoadMUS(file);

    if (music == NULL)
    {
        fprintf(stderr, "[Engine] Failed to load music: %s\n", file);
    }

    Mix_VolumeMusic(10);
    Mix_PlayMusic(music, -1);
}

void sound_stop()
{
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}