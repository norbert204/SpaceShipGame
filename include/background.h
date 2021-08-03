#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "engine/window.h"
#include "engine/utilities.h"
#include "engine/structs.h"

#define BG_TARGET_POS WINDOW_WIDTH

#define BG_SMALL_COUNT 6
#define BG_BIG_COUNT 2

#define BG_SMALL_SIZE_X WINDOW_WIDTH / 2.0f
#define BG_SMALL_SIZE_Y WINDOW_HEIGHT / 2.0f

#define BG_BIG_SIZE_X WINDOW_WIDTH
#define BG_BIG_SIZE_Y WINDOW_HEIGHT

#define BG_SMALL_SPEED 100
#define BG_BIG_SPEED 50

extern Vector2D smaller_bg_positions[BG_SMALL_COUNT];
extern Vector2D bigger_bg_positions[BG_BIG_COUNT];

void background_init();
void background_update();
void background_render(SDL_Texture *texture);

#endif
