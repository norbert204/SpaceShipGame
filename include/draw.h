#ifndef DRAW_H
#define DRAW_H

#include "transform.h"
#include "window.h"
#include "mathe.h"

#define COLOR_WHITE (Color) { 255, 255, 255 }
#define COLOR_BLACK (Color) { 0, 0, 0 }
#define COLOR_RED (Color) { 255, 0, 0 }
#define COLOR_YELLOW (Color) { 255, 255, 0 }

void draw_rectangle(const int x, const int y, const int w, const int h, const Color color);
void draw_rectangle1(const Vector2D position, const Size2D size, const Color color);
void draw_circle(const float x, const float y, const float r);

#endif