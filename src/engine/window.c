#include "engine/window.h"

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Window *window_getWindow()
{
    return window;
}

SDL_Renderer *window_getRenderer()
{
    return renderer;
}

bool window_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        fprintf(stderr, "[Engine] SDL couldn't initialize: %s\n", SDL_GetError());
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        fprintf(stderr, "[Engine] SDL_Image couldn't initialize: %s\n", SDL_GetError());
        return false;
    }
    if (!text_init())
    {
        return false;
    }
    if (!sound_init())
    {
        return false;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        fprintf(stderr, "[Engine] Couldn't create Window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        fprintf(stderr, "[Engine] Couldn't create Renderer: %s\n", SDL_GetError());
    }

    return true;
}

void window_setFullscreen()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void window_clear()
{
    SDL_RenderClear(renderer);
}

void window_render(const Vector2D position, const Size2D sprite_size, SDL_Texture *texture)
{
    window_renderEx(position, sprite_size, sprite_size, VECTOR2D_ZERO, 0, COLOR_WHITE, texture);
}

void window_renderSprite(const Transform transform, const Sprite sprite)
{
    Vector2D image_position;
    image_position.x = sprite.animations[sprite.current_animation].frames[sprite.animations[sprite.current_animation].current_frame].x;
    image_position.y = sprite.animations[sprite.current_animation].frames[sprite.animations[sprite.current_animation].current_frame].y;
    
    Size2D target_size;
    target_size.w = sprite.tile_size.w * transform.scale;
    target_size.h = sprite.tile_size.h * transform.scale;

    window_renderEx(transform.position, sprite.tile_size, target_size, image_position, transform.angle, COLOR_WHITE, sprite.texture);
}

void window_renderEx(const Vector2D position, const Size2D sprite_size, const Size2D target_size, const Vector2D image_position, double angle, SDL_Color color, SDL_Texture *texture)
{
    SDL_Rect pos_rect;
    pos_rect.x = position.x;
    pos_rect.y = position.y;
    pos_rect.w = target_size.w;
    pos_rect.h = target_size.h;

    SDL_Rect image_rect;
    image_rect.x = image_position.x;
    image_rect.y = image_position.y;
    image_rect.w = sprite_size.w;
    image_rect.h = sprite_size.h;

    SDL_Point center;
    center.x = target_size.w / 2;
    center.y = target_size.h / 2;

    SDL_SetTextureAlphaMod(texture, color.a);
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

    SDL_RenderCopyEx(renderer, texture, &image_rect, &pos_rect, angle, &center, SDL_FLIP_NONE);

    SDL_SetTextureAlphaMod(texture, 255);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void window_display()
{
    SDL_RenderPresent(renderer);
}

int window_getRefreshRate()
{
    int display_index = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(display_index, 0, &mode);

    return mode.refresh_rate;
}

void window_stop()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    window = NULL;
    renderer = NULL;
    
    IMG_Quit();
    SDL_Quit();
}

