#include "missile.h"

Missile missiles[MISSILE_MAX];
int missiles_top;
float missile_cooldown;

void missile_init()
{
    missiles_top = 0;
    missile_cooldown = 0;
}

void missile_create(Vector2D position)
{
    if (missiles_top < MISSILE_MAX)
    {
        Vector2D colCenter = { 16, 2 };
        Size2D colSize = { 32, 4 };

        missiles[missiles_top] = (Missile) { (Transform) { position, 1, 0 }, (BoxCollider) { colCenter, colSize } };
        missiles_top++;
    }
}

void missile_handleEvent(SDL_Event *event, Vector2D shipPosition)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_SPACE)
            {
                if (missile_cooldown <= 0) {
                    missile_create((Vector2D) { shipPosition.x + 1024 / 4 - 40, shipPosition.y + 64 });
                    missile_cooldown = MISSILE_COOLDOWN;
                }
            }
            break;
    }
}

void missile_update()
{
    for (int i = 0; i < missiles_top; i++)
    {
        missiles[i].transform.position.x += MISSILE_SPEED * delta_time;
    }

    for (int i = missiles_top - 1; i >= 0; i--)
    {
        if (missiles[i].transform.position.x > WINDOW_WIDTH)
        {
            missile_delete(i);
        }
        else
        {
            int meteor_index = -1;
            for (int j = meteors_top - 1; j >= 0; j--)
            {
                if (colliding_circle_box(meteors[j].transform, missiles[i].transform, meteors[j].collider, missiles[i].collider))
                {
                    meteor_index = j;
                    break;
                }
            }

            if (meteor_index > -1)
            {
                meteors_delete(meteor_index);
                missile_delete(i);
            }
        }
    }

    if (missile_cooldown > 0)
    {
        missile_cooldown -= delta_time;
    }
}

void missile_render(SDL_Texture *texture)
{
    for (int i = 0; i < missiles_top; i++) 
    {
        window_renderEx(missiles[i].transform.position, (Size2D) { 1, 1 }, missiles[i].collider.size, 0, COLOR_YELLOW, texture);
    }
}

void missile_renderHUD(SDL_Texture *tex_blank)
{
    window_renderEx((Vector2D) { 0, WINDOW_HEIGHT - 10 }, (Size2D) { 1, 1 }, (Size2D) { WINDOW_WIDTH, 10 }, 0, COLOR_YELLOW, tex_blank);
    window_renderEx((Vector2D) { WINDOW_WIDTH - (missile_cooldown / MISSILE_COOLDOWN) * WINDOW_WIDTH + 1, WINDOW_HEIGHT - 10 }, (Size2D) { 1, 1 }, (Size2D) { (missile_cooldown / MISSILE_COOLDOWN) * WINDOW_WIDTH, 10 }, 0, COLOR_BLACK, tex_blank);
}

void missile_delete(int id)
{
    if (id < missiles_top && id >= 0)
    {
        for (int i = id; i < missiles_top - 1; i++)
        {
            missiles[i] = missiles[i+1];
        }

        missiles_top--;
    }
}