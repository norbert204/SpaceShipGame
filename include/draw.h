#ifndef DRAW_H
#define DRAW_H

#include "transform.h"
#include "window.h"
#include "mathe.h"

Color color_white();

void draw_rectangle(const int x, const int y, const int w, const int h, const Color color);
void draw_rectangle1(const Vector2D position, const Size2D size, const Color color);
void draw_circle(const float x, const float y, const float r);

#endif