#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../engine/structs.h"

typedef struct
{
    bool loop;
    Vector2Di *frames;
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

#endif