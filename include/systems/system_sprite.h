#ifndef SYSTEM_SPRITE_H
#define SYSTEM_SPRITE_H

#include "../components/component_sprite.h"
#include "../engine/structs.h"
#include "../entity.h"
#include "../engine/time.h"
#include "../engine/window.h"

void sprite_createAnimation(Sprite *sprite, const int index, const bool loop, const float speed, const int number_of_frames, const Vector2Di frames[]);

void sprite_update(Entity *entity);
void sprite_render(EntityList list);

#endif