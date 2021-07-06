#ifndef SPRITE_H
#define SPRITE_H

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "transform.h"

typedef struct
{
    bool loop;
    int startingFrame;
    int frameCount;
    float speed;
} Animation;

typedef struct 
{
    SDL_Texture *texture;

    Animation *animations;
    int numberOfAnimations;
    int currentAnimation;

    Size2D tileSize;
} Sprite;

Sprite sprite_create(SDL_Texture *texture, int numberOfAnimations, Size2D tileSize);
void sprite_destroy(Sprite *sprite);

#endif