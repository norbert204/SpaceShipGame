#ifndef SYSTEM_PLAYER_H
#define SYSTEM_PLAYER_H

#include <SDL2/SDL.h>

#include "../engine/structs.h"
#include "../engine/inputs.h"
#include "../entity.h"

void player_update(Entity *entity);

#endif