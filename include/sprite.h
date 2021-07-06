#ifndef SPRITE_H
#define SPRITE_H

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "transform.h"
#include "utilities.h"

typedef struct
{
    bool loop;
    int starting_frame;
    int frame_count;
    int current_frame;
    float speed;
} Animation;

typedef struct 
{
    SDL_Texture *texture;

    Animation *animations;
    int number_of_animations;
    int current_animation;

    float animation_frame_countdown;

    Size2D tile_size;
} Sprite;

Sprite sprite_create(SDL_Texture *texture, const int number_of_animations, const Size2D tile_size);
void sprite_update(Sprite *sprite);
void sprite_destroy(Sprite *sprite);

#endif