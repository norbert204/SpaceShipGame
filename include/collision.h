#ifndef COLLISION_H
#define COLLISION_H

#include "transform.h"

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