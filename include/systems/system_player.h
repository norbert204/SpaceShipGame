#ifndef SYSTEM_PLAYER_H
#define SYSTEM_PLAYER_H

#include <SDL2/SDL.h>

#include "../engine/structs.h"
#include "../engine/inputs.h"
#include "../components/component_sprite.h"
#include "../entity.h"
#include "system_sprite.h"

#define PLAYER_SPEED 500

void player_init(EntityList *list, SDL_Texture *texture);
void player_update(Entity *entity);

#endif