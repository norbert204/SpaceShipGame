#include "sprite.h"

Sprite sprite_create(SDL_Texture *texture, int numberOfAnimations, Size2D tileSize)
{
    Sprite sprite;
    sprite.texture = texture;
    sprite.animations = malloc(sizeof(Animation) * numberOfAnimations);
    sprite.tileSize = tileSize;
    return sprite;
}

void sprite_destroy(Sprite *sprite)
{
    free(sprite->animations);
}