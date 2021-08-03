#ifndef SCENE_H
#define SCENE_H

#include "entity.h"

#define SYSTEM_COUNT 5

typedef struct
{
    EntityList entities;
    u_int8_t enabled_systems[SYSTEM_COUNT];
} Scene;

#endif