#include "sprite.h"

Sprite sprite_create(const SDL_Texture *texture, const int number_of_animations, const Size2D tile_size)
{
    Sprite sprite;
    sprite.texture = texture;
    sprite.animations = malloc(sizeof(Animation) * number_of_animations);
    sprite.tile_size = tile_size;
    return sprite;
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
    free(sprite->animations);
}