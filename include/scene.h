#ifndef SCENE_H
#define SCENE_H

#define SYSTEM_ID_SPRITE 0
#define SYSTEM_ID_COLLIDER 1
#define SYSTEM_ID_RIGIDBODY 2
#define SYSTEM_ID_PLAYER 3
#define SYSTEM_ID_METEORS 4

#define SYSTEM_COUNT 5

#include "entity.h"

#include "systems/system_sprite.h"
#include "systems/system_collider.h"
#include "systems/system_rigidbody.h"
#include "systems/system_player.h"
#include "systems/system_meteors.h"

#include "engine/textures.h"

typedef struct
{
    EntityList entities;
    u_int8_t enabled_systems[SYSTEM_COUNT];
} Scene;

extern Scene scenes[];

void scene_load(const int id);
void scene_update();
Scene *scene_getCurrentScene();

#endif