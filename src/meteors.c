#include "meteors.h"

int meteors_top;
Meteor meteors[METEORS_MAX];

void meteors_init()
{
    meteors_top = 0;
}

void meteors_update()
{
    for (int i = 0; i < meteors_top; i++)
    {
        meteors[i].transform.angle += 100 * delta_time;
        meteors[i].transform.position.x -= METEOR_SPEED * delta_time;
    }

    for (int i = meteors_top - 1; i >= 0; i--)
    {
        if (meteors[i].transform.position.x < -256)
        {
            meteors_delete(i);
            i--;
        }
    }
}

void meteors_render(SDL_Texture *texture, Size2D sprite_size)
{
    for (int i = 0; i < meteors_top; i++) 
    {
        window_renderTransform(meteors[i].transform, sprite_size, texture);
        draw_circle(meteors[i].transform.position.x + 32 * meteors[i].transform.scale, meteors[i].transform.position.y + 32 * meteors[i].transform.scale, 32 * meteors[i].transform.scale);
    }
}

void meteors_add()
{
    if (meteors_top < METEORS_MAX)
    {
        Transform t = (Transform) {(Vector2D) { WINDOW_WIDTH + 128 + rand() % 128, rand() % (WINDOW_HEIGHT - 128) }, 1 + rand() % 2, rand() % 360};
        CircleCollider c = (CircleCollider) { (Vector2D) { 32 * t.scale, 32 * t.scale }, 32 * t.scale };
        meteors[meteors_top] = (Meteor) { t, c };
        meteors_top++;
    }
}

void meteors_delete(int id)
{
    if (id < meteors_top && id >= 0)
    {
        for (int i = id; i < meteors_top - 1; i++)
        {
            meteors[i] = meteors[i+1];
        }

        meteors_top--;
    }
}