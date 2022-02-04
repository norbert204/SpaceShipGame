#ifndef WINDOW_H
#define WINDOW_H

#define TITLE "SpaceShipGame"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "structs.h"
#include "draw.h"
#include "../components/component_sprite.h"
#include "../components/component_transform.h"
#include "../entity.h"

#include "sound.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

SDL_Window *window_getWindow();
SDL_Renderer *window_getRenderer();

bool window_init();
void window_setFullscreen();
void window_clear();

void window_render(const Vector2D position, const Size2D sprite_size, SDL_Texture *texture);
void window_renderSprite(const Transform transform, const Sprite sprite);
//void window_renderEntityList(const EntityList list);
//void window_renderTransform(const Transform transform, const Size2D sprite_size, SDL_Texture *texture);
void window_renderEx(const Vector2D position, const Size2D sprite_size, const Size2D target_size, const Vector2D image_position, double angle, SDL_Color color, SDL_Texture *texture);

void window_display();
int window_getRefreshRate();
void window_stop();

#endif
