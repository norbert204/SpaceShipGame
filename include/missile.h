#ifndef MISSILE_H
#define MISSILE_H

#include <SDL2/SDL.h>

#include "transform.h"
#include "collision.h"
#include "draw.h"
#include "window.h"
#include "utilities.h"
#include "meteors.h"

#define MISSILE_MAX 2
#define MISSILE_SPEED 900

typedef struct
{
    Transform transform;
    BoxCollider collider;
} Missile;

extern Missile missiles[MISSILE_MAX];
extern int missiles_top;

void missile_init();
void missile_create(Vector2D position);
void missile_handleEvent(SDL_Event *event, Vector2D shipPosition);
void missile_update();
void missile_render(SDL_Texture *texture);
void missile_delete(int id);

#endif