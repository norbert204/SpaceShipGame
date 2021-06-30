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

int colliding_circle_box(Transform a, Transform b, CircleCollider ac, BoxCollider bc);
int colliding_circle_circle(Transform a, Transform b, CircleCollider ac, CircleCollider bc);

#endif