#ifndef STRUCTS_H
#define STRUCTS_H

#define VECTOR2D_ZERO (Vector2D) { 0, 0 }

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

#endif