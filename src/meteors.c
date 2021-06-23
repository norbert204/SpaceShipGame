#include "meteors.h"

int meteors_top;
Transform meteors[METEORS_MAX];

void meteors_init()
{
    meteors_top = 0;
}

void meteors_update()
{
    for (int i = 0; i < meteors_top; i++)
    {
        meteors[i].angle += 100 * delta_time;
    }
}

void meteors_render(SDL_Texture *texture, Size2D sprite_size)
{
    for (int i = 0; i < meteors_top; i++) 
    {
        window_renderTransform(meteors[i], sprite_size, texture);
        draw_circle(meteors[i].position.x + 32 * meteors[i].scale, meteors[i].position.y + 32 * meteors[i].scale, 32 * meteors[i].scale);
    }
}

void meteors_create()
{
    if (meteors_top != METEORS_MAX)
    {
        meteors[meteors_top] = (Transform) {(Vector2D) { 128, rand() % (WINDOW_HEIGHT / 2) }, 1 + rand() % 2, rand() % 360};
        meteors_top++;
    }
}