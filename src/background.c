#include "background.h"

Vector2D smaller_bg_positions[BG_SMALL_COUNT];
Vector2D bigger_bg_positions[BG_BIG_COUNT];

void background_init()
{
    smaller_bg_positions[0] = (Vector2D) { 0.0f, 0.0f };
    smaller_bg_positions[1] = (Vector2D) { 0.0f, BG_SMALL_SIZE_Y };
    smaller_bg_positions[2] = (Vector2D) { BG_SMALL_SIZE_X, 0.0f };
    smaller_bg_positions[3] = (Vector2D) { BG_SMALL_SIZE_X, BG_SMALL_SIZE_Y };
    smaller_bg_positions[4] = (Vector2D) { BG_SMALL_SIZE_X * 2, 0.0f };
    smaller_bg_positions[5] = (Vector2D) { BG_SMALL_SIZE_X * 2, BG_SMALL_SIZE_Y };

    bigger_bg_positions[0] = (Vector2D) { 0.0f, 0.0f };
    bigger_bg_positions[1] = (Vector2D) { BG_BIG_SIZE_X, 0.0f };
}

void background_update()
{
    for (int i = 0; i < BG_BIG_COUNT; i++)
    {
        bigger_bg_positions[i].x -= BG_BIG_SPEED * delta_time;
        if (bigger_bg_positions[i].x < -BG_BIG_SIZE_X)
        {
            bigger_bg_positions[i].x += BG_TARGET_POS + BG_BIG_SIZE_X;
        }
    }

    for (int i = 0; i < BG_SMALL_COUNT; i++)
    {
        smaller_bg_positions[i].x -= BG_SMALL_SPEED * delta_time;
        if (smaller_bg_positions[i].x < -BG_SMALL_SIZE_X)
        {
            smaller_bg_positions[i].x += BG_TARGET_POS + BG_SMALL_SIZE_X;
        }
    }
}

void background_render(SDL_Texture *texture)
{
    for (int i = 0; i < BG_SMALL_COUNT; i++)
    {
        window_renderEx(smaller_bg_positions[i], (Size2D) { 128, 64 }, (Size2D) { BG_SMALL_SIZE_X, BG_SMALL_SIZE_Y}, 0, (Color) {255, 255, 255, 100}, texture);
    }
    for (int i = 0; i < BG_BIG_COUNT; i++)
    {
        window_renderEx(bigger_bg_positions[i], (Size2D) { 128, 64 }, (Size2D) { BG_BIG_SIZE_X, BG_BIG_SIZE_Y}, 0, (Color) {255, 255, 255, 100}, texture);
    }
}

void background_destroy()
{
    /*free(smaller_bg_positions);
    free(bigger_bg_positions);

    smaller_bg_positions = NULL;
    bigger_bg_positions = NULL;*/
}
