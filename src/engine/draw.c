#include "engine/draw.h"

static TTF_Font *font = NULL;

int text_init()
{
    if (TTF_Init() == -1) 
    {
        fprintf(stderr, "[Engine] SDL_ttf couldn't initialize: %s\n", SDL_GetError());
        return 0;
    }
 
    font = TTF_OpenFont("res/PressStart2P.ttf", 40);
    if (font == NULL)
    {
        fprintf(stderr, "[Engine] Failed to load font %s: %s\n", "res/PressStart2P", TTF_GetError());
        return 0;
    }

    return 1;
}

void draw_rectangle(const int x, const int y, const int w, const int h, const SDL_Color color)
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

void draw_rectangle1(const Vector2D position, const Size2D size, const SDL_Color color)
{
    draw_rectangle(position.x, position.y, size.w, size.h, color);
}

void draw_filledRectangle(const int x, const int y, const int w, const int h, SDL_Color color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(window_getRenderer(), color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(window_getRenderer(), &rect);

    SDL_SetRenderDrawColor(window_getRenderer(), 0, 0, 0, 255);
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

void draw_text(const char *text, const Vector2D position)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, (SDL_Color) { 255, 255, 255, 255 } );
    if (surface == NULL)
    {
        fprintf(stderr, "[Engine] Unable to render text surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(window_getRenderer(), surface);
    if (texture == NULL)
    {
        fprintf(stderr, "[Engine] Unable to create texture from surface: %s\n", SDL_GetError());
    }

    window_render(position, (Size2D) {surface->w, surface->h}, texture);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void text_stop()
{
    TTF_CloseFont(font);
    TTF_Quit();
}