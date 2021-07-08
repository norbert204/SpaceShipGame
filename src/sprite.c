#include "sprite.h"

Sprite sprite_create(SDL_Texture *texture, const int number_of_animations, const Size2D tile_size)
{
    Sprite sprite;
    sprite.texture = texture;
    sprite.animations = malloc(sizeof(Animation) * number_of_animations);
    sprite.number_of_animations = number_of_animations;
    sprite.current_animation = 0;
    sprite.tile_size = tile_size;
    
    return sprite;
}

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

Animation sprite_getCurrentAnimation(const Sprite sprite)
{
    return sprite.animations[sprite.current_animation];
}

void sprite_update(Sprite *sprite)
{
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

void sprite_destroy(Sprite *sprite)
{
    for (int i = 0; i < sprite->number_of_animations; i++)
    {
        free(sprite->animations[i].frames);
    }
    free(sprite->animations);
}