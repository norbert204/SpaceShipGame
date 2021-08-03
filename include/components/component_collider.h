#ifndef COMPONENT_COLLISION_H
#define COMPONENT_COLLISION_H

#include "../engine/structs.h"

typedef struct
{
    Vector2D center;
    Size2D size;
} BoxCollider;

typedef struct
{
    Vector2D center;
    float radius;
} CircleCollider;

#endif