#ifndef MATHF_H
#define MATHF_H

#include <stdio.h>

#include "structs.h"

#define TRANSFORM_ZERO (Transform) { VECTOR2D_ZERO, 1, 0 }

typedef struct
{
    Vector2D position;
    float scale;
    double angle;
} Transform;

extern Transform *transform_list;
static int list_length;
static int list_capacity;

#endif