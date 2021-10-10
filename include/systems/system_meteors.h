#ifndef SYSTEM_METEORS_H
#define SYSTEM_METEORS_H

#include <SDL2/SDL.h>

#include "../entity.h"
#include "../engine/time.h"
#include "../engine/window.h"
#include "../engine/textures.h"
#include "system_sprite.h"

#define METEORS_MAX 100
#define METEOR_SPEED 200
#define METEOR_SPAWN_TIME 1

void meteors_init(SDL_Texture *texture);
void meteors_update(EntityList *list);
int meteors_updateEntity(EntityList *list, Entity *entity);

#endif