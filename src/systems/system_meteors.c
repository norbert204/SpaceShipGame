#include "systems/system_meteors.h"

static int meteor_count;
static float meteor_spawn_timer;

static SDL_Texture *m_texture;

void meteors_init(SDL_Texture *texture)
{
    m_texture = texture;

    meteor_count = 0;
    meteor_spawn_timer = METEOR_SPAWN_TIME;
}

void meteors_update(EntityList *list)
{
    meteor_spawn_timer -= time_getDeltaTime();
    

    if (meteor_spawn_timer <= 0)
    {
        Entity tmp = entity_create();
        entity_addTransformComponent(&tmp, (Vector2D) { WINDOW_WIDTH + 128 + rand() % 128, rand() % (WINDOW_HEIGHT - 128) }, 1 + rand() % 2, rand() % 360);
        entity_addSpriteComponent(&tmp, m_texture, 1, (Size2D) { 128, 128 });

        Vector2Di frames[1];
        frames[0] = (Vector2Di) { 0, 0 };
        sprite_createAnimation(tmp.components.sprite, 0, false, 0, 1, frames);

        entity_addRigidbodyComponent(&tmp);
        tmp.components.rigidbody->velocity = (Vector2D) { -1, 0 };
        tmp.components.rigidbody->speed = METEOR_SPEED;

        tmp.type = meteor;

        entity_addToList(list, tmp);

        meteor_spawn_timer += METEOR_SPAWN_TIME;
    }
}

int meteors_updateEntity(EntityList *list, Entity *entity)
{
    if (entity->components.transform->position.x < -256)
    {
        entity_delete(list, entity->id);
        return 1;
    }
    
    entity->components.transform->angle -= 100 * time_getDeltaTime();   
    return 0;
}