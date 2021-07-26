#ifndef METEORS_H
#define METEORS_H

#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "transform.h"
#include "collision.h"
#include "window.h"
#include "draw.h"
#include "utilities.h"

#define METEORS_MAX 100
#define METEOR_SPEED 200

typedef struct
{
    Transform transform;
    CircleCollider collider;
} Meteor;

extern Meteor meteors[METEORS_MAX];
extern int meteors_top;

void meteors_init();
void meteors_update();
void meteors_render(SDL_Texture *texture, Size2D sprite_size);
void meteors_add();
void meteors_delete(int id);

#endif