#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine/window.h"

typedef struct
{
    char *name;
    SDL_Texture *texture;
} Texture;

extern Texture *loaded_textures;

void textures_load(const char *path, const char *name);
SDL_Texture *textures_getTexture(char *name);
void textures_destroy();

#endif