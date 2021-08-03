#include "systems/system_meteors.h"

static int meteor_count;
static float meteor_spawn_timer;

void meteors_init()
{
    meteor_count = 0;
    meteor_spawn_timer = METEOR_SPAWN_TIME;
}

void meteors_update(EntityList *list, SDL_Texture *texture)
{
    meteor_spawn_timer -= delta_time;
    if (meteor_spawn_timer <= 0)
    {
        Entity tmp = entity_create();
        entity_addTransformComponent(&tmp, (Vector2D) { WINDOW_WIDTH + 128 + rand() % 128, rand() % (WINDOW_HEIGHT - 128) }, 1 + rand() % 2, rand() % 360);
        entity_addSpriteComponent(&tmp, texture, 1, (Size2D) { 128, 128 });

        Vector2Di frames[1];
        frames[0] = (Vector2Di) { 0, 0 };
        sprite_createAnimation(tmp.components.sprite, 0, false, 0, 1, frames);

        entity_addRigidbodyComponent(&tmp);
        tmp.components.rigidbody->velocity = (Vector2D) { -1, 0 };
        tmp.components.rigidbody->speed = METEOR_SPEED;

        entity_addToList(list, tmp);

        meteor_spawn_timer += METEOR_SPAWN_TIME;
    }
}