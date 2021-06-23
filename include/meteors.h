#ifndef METEORS_H
#define METEORS_H

#include <stdlib.h>
#include <time.h>

#include "transform.h"
#include "collision.h"
#include "window.h"
#include "draw.h"
#include "utilities.h"

#define METEORS_MAX 100

typedef struct
{
    Transform position;
    CircleCollider collider;
} Meteor;

extern Transform meteors[METEORS_MAX];

extern int meteors_top;

void meteors_init();
void meteors_update();
void meteors_render(SDL_Texture *texture, Size2D sprite_size);
void meteors_create();

#endif