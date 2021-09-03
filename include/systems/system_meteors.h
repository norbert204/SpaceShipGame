#ifndef SYSTEM_METEORS_H
#define SYSTEM_METEORS_H

#include <SDL2/SDL.h>

#include "../entity.h"
#include "../engine/utilities.h"
#include "../engine/window.h"
#include "system_sprite.h"

#define METEORS_MAX 100
#define METEOR_SPEED 200
#define METEOR_SPAWN_TIME 5

void meteors_init();
void meteors_update(EntityList *list, SDL_Texture *texture);
int meteors_updateEntity(EntityList *list, Entity *entity);

#endif