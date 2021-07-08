#ifndef MATHF_H
#define MATHF_H

#include <stdio.h>

typedef struct
{
    float x, y;
} Vector2D;

typedef struct
{
    int x, y;
} Vector2Di;

typedef struct
{
    int w, h;
} Size2D;

typedef struct
{
    Vector2D position;
    float scale;
    double angle;
} Transform;

typedef struct
{
    int r, g, b, a;
} Color;

Vector2D vector2D_zero();
Transform transform_zero();

#endif