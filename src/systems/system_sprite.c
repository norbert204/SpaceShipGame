#include "systems/system_sprite.h"

void sprite_createAnimation(Sprite *sprite, const int index, const bool loop, const float speed, const int number_of_frames, const Vector2Di frames[])
{
    sprite->animations[index].frames = malloc(sizeof(Vector2Di) * number_of_frames);
    
    for (int i = 0; i < number_of_frames; i++)
    {
        sprite->animations[index].frames[i] = frames[i];
    }
    
    sprite->animations[index].frame_count = number_of_frames;
    sprite->animations[index].current_frame = 0;
    sprite->animations[index].loop = loop;
    sprite->animations[index].speed = speed;
}

void sprite_update(Entity *entity)
{
    if (entity->components.sprite != NULL)
    {
        Sprite *sprite = entity->components.sprite;

        if (sprite->animations[sprite->current_animation].frame_count > 1)
        {
            if (sprite->animation_frame_countdown > 0)
            {
                sprite->animation_frame_countdown -= delta_time;

                if (sprite->animation_frame_countdown <= 0)
                {
                    if (sprite->animations[sprite->current_animation].current_frame < sprite->animations[sprite->current_animation].frame_count - 1)
                    {
                        sprite->animations[sprite->current_animation].current_frame++;
                    }
                    else if (sprite->animations[sprite->current_animation].loop)
                    {
                        sprite->animations[sprite->current_animation].current_frame = 0;
                    }
                    sprite->animation_frame_countdown = sprite->animations[sprite->current_animation].speed;
                }
            }
        }
    }
}

void sprite_render(EntityList list)
{
    EntityListItem *item = list;
    while (item != NULL)
    {
        if (item->item.components.sprite != NULL)
        {
            if (item->item.components.transform != NULL)
            {
                window_renderSprite(*item->item.components.transform, *item->item.components.sprite);
            }
        }
        item = item->next;
    }
}