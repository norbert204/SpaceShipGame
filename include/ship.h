#ifndef SHIP_H
#define SHIP_H

#include <stdbool.h>

#include "window.h"
#include "transform.h"
#include "collision.h"
#include "utilities.h"

#define SHIP_SPEED 500

typedef struct
{
    Transform transform;
    Vector2D velocity;
    BoxCollider collision;
    bool alive;
} Ship;

void ship_init(Ship *ship);
void ship_handleEvent(Ship *ship, SDL_Event *event);
void ship_update(Ship *ship);

#endif