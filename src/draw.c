#include "draw.h"

Color color_white()
{
    return (Color) { 255, 255, 255, 255 };
}

void draw_rectangle(const int x, const int y, const int w, const int h, const Color color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(window_getRenderer(), color.r, color.g, color.b, color.a);

    SDL_RenderDrawRect(window_getRenderer(), &rect);

    SDL_SetRenderDrawColor(window_getRenderer(), 0, 0, 0, 255);
}

void draw_rectangle1(const Vector2D position, const Size2D size, const Color color)
{
    draw_rectangle(position.x, position.y, size.w, size.h, color);
}

void draw_circle(const float x, const float y, const float r)
{
    SDL_SetRenderDrawColor(window_getRenderer(), 255, 255, 255, 255);

    for (int i = 0; i < 360; i++)
    {
        SDL_RenderDrawLine(window_getRenderer(), x + SDL_sin(i * M_PI/180.0f) * r, y + SDL_cos(i * M_PI/180.0f) * r, x + SDL_sin((i + 1) * M_PI/180.0f) * r, y + SDL_cos((i + 1) * M_PI/180.0f) * r);
    }

    SDL_SetRenderDrawColor(window_getRenderer(), 0, 0, 0, 255);
}