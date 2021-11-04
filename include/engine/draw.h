#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

#include "structs.h"
#include "window.h"
#include "mathe.h"

#define COLOR_WHITE (SDL_Color) { 255, 255, 255, 255 }
#define COLOR_BLACK (SDL_Color) { 0, 0, 0, 255 }
#define COLOR_RED (SDL_Color) { 255, 0, 0, 255 }
#define COLOR_GREEN (SDL_Color) { 0, 255, 0, 255 }
#define COLOR_BLUE (SDL_Color) { 0, 0, 255, 255 }
#define COLOR_YELLOW (SDL_Color) { 255, 255, 0, 255 }

int text_init();

void draw_rectangle(const int x, const int y, const int w, const int h, const SDL_Color color);
void draw_rectangle1(const Vector2D position, const Size2D size, const SDL_Color color);
void draw_filledRectangle(const int x, const int y, const int w, const int h, SDL_Color color);
void draw_circle(const float x, const float y, const float r);
void draw_text(const char *text, const Vector2D position);

void text_stop();

#endif