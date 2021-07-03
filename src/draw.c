#include "draw.h"

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

/*
    https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
*/
void draw_circle(const float x, const float y, const float r)
{
    SDL_SetRenderDrawColor(window_getRenderer(), 255, 255, 255, 255);

    const int d = r * 2;

    int _x = r - 1;
    int _y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - d);

    while (_x >= _y)
    {
        SDL_RenderDrawPoint(renderer, x + _x, y - _y);
        SDL_RenderDrawPoint(renderer, x + _x, y + _y);
        SDL_RenderDrawPoint(renderer, x - _x, y - _y);
        SDL_RenderDrawPoint(renderer, x - _x, y + _y);
        SDL_RenderDrawPoint(renderer, x + _y, y - _x);
        SDL_RenderDrawPoint(renderer, x + _y, y + _x);
        SDL_RenderDrawPoint(renderer, x - _y, y - _x);
        SDL_RenderDrawPoint(renderer, x - _y, y + _x);

        if (error <= 0)
        {
            _y++;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            _x--;
            ty += 2;
            error += (tx - d);
        }
    }

    SDL_SetRenderDrawColor(window_getRenderer(), 0, 0, 0, 255);
}

void draw_text(char *text)
{
    //  TODO: ...yes
}