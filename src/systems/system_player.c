#include "systems/system_player.h"

void player_init(EntityList *list, SDL_Texture *texture) 
{
    Entity entity = entity_create();
    entity_addTransformComponent(&entity, (Vector2D) { 100, 100 }, 1, 0);
    entity_addSpriteComponent(&entity, texture, 3, (Size2D) { 1024 / 4, 128 });

    Vector2Di frames[1] = { (Vector2Di) { 256, 0 } };
    sprite_createAnimation(entity.components.sprite, 0, false, 0, 1, frames);
    
    frames[0].x = 0;
    sprite_createAnimation(entity.components.sprite, 1, false, 0, 1, frames);
    
    frames[0].x = 512;
    sprite_createAnimation(entity.components.sprite, 2, false, 0, 1, frames);

    entity_addBoxColliderComponent(&entity, (Vector2D) { 1024 / 8 + 20, 64 }, (Size2D) { (1024 / 4) - 120 , 60 });
    entity_addRigidbodyComponent(&entity);
    entity.components.rigidbody->speed = PLAYER_SPEED;
    entity.type = player;

    entity_addToList(list, entity);
}

void player_update(Entity *entity)
{
    Vector2D velocity = (Vector2D) 
    {
        keyboard_getAxisX(),
        keyboard_getAxisY()
    };

    if ((velocity.x < 0 && entity->components.transform->position.x + entity->components.box_collider->center.x - entity->components.box_collider->size.w / 2 <= 0) ||
        (velocity.x > 0 && entity->components.transform->position.x + entity->components.box_collider->center.x + entity->components.box_collider->size.w / 2 >= 1280))
    {
        velocity.x = 0;
    }

    if (velocity.y < 0) 
    {
        if (velocity.y < 0 && entity->components.transform->position.y + entity->components.box_collider->center.y - entity->components.box_collider->size.h / 2 <= 0)
        {
            velocity.y = 0;
        }
        else 
        {
            entity->components.sprite->current_animation = 1;
        }
    }
    else if (velocity.y > 0)
    {
        if (velocity.y > 0 && entity->components.transform->position.y + entity->components.box_collider->center.y + entity->components.box_collider->size.h / 2 >= 720)
        {
            velocity.y = 0;
        }
        else 
        {
            entity->components.sprite->current_animation = 2;
        }    
    }
    else 
    {
        entity->components.sprite->current_animation = 0;
    }
    
    entity->components.rigidbody->velocity = velocity;
}