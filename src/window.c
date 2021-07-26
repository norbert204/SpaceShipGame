#include "window.h"

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

void window_clear()
{
    SDL_RenderClear(renderer);
}

void window_render(const Vector2D position, const Size2D sprite_size, SDL_Texture *texture)
{
    SDL_Rect pos_rect;
    pos_rect.x = position.x;
    pos_rect.y = position.y;
    pos_rect.w = sprite_size.w;
    pos_rect.h = sprite_size.h;

    SDL_Rect image_rect;
    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.w = sprite_size.w;
    image_rect.h = sprite_size.h;

    SDL_Point center;
    center.x = sprite_size.w / 2;
    center.y = sprite_size.h / 2;

    SDL_SetTextureAlphaMod(texture, 255);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_RenderCopyEx(renderer, texture, &image_rect, &pos_rect, 0, &center, SDL_FLIP_NONE);
}

void window_renderSprite(const Vector2D position, const Sprite sprite)
{
    SDL_Rect pos_rect;
    pos_rect.x = position.x;
    pos_rect.y = position.y;
    pos_rect.w = sprite.tile_size.w;
    pos_rect.h = sprite.tile_size.h;

    SDL_Rect image_rect;
    Animation anim = sprite_getCurrentAnimation(sprite);
    image_rect.x = anim.frames[anim.current_frame].x;
    image_rect.y = anim.frames[anim.current_frame].y;
    image_rect.w = sprite.tile_size.w;
    image_rect.h = sprite.tile_size.h;

    SDL_Point center;
    center.x = sprite.tile_size.w / 2;
    center.y = sprite.tile_size.h / 2;

    SDL_SetTextureAlphaMod(sprite.texture, 255);
    SDL_SetTextureColorMod(sprite.texture, 255, 255, 255);
    SDL_RenderCopyEx(renderer, sprite.texture, &image_rect, &pos_rect, 0, &center, SDL_FLIP_NONE);
}

void window_renderEntityList(const EntityList list)
{
    EntityListItem *item = list;
    while (item != NULL)
    {
        if (item->item.transform != NULL && item->item.sprite != NULL)
        {
            SDL_Rect pos_rect;
            pos_rect.x = item->item.transform->position.x;
            pos_rect.y = item->item.transform->position.y;
            pos_rect.w = item->item.sprite->tile_size.w * item->item.transform->scale;
            pos_rect.h = item->item.sprite->tile_size.h * item->item.transform->scale;

            SDL_Rect image_rect;
            Animation anim = sprite_getCurrentAnimation(*item->item.sprite);
            image_rect.x = anim.frames[anim.current_frame].x;
            image_rect.y = anim.frames[anim.current_frame].y;
            image_rect.w = item->item.sprite->tile_size.w;
            image_rect.h = item->item.sprite->tile_size.h;

            SDL_Point center;
            center.x = item->item.sprite->tile_size.w * item->item.transform->scale / 2;
            center.y = item->item.sprite->tile_size.h * item->item.transform->scale / 2;

            SDL_SetTextureAlphaMod(item->item.sprite->texture, 255);
            SDL_SetTextureColorMod(item->item.sprite->texture, 255, 255, 255);
            SDL_RenderCopyEx(renderer, item->item.sprite->texture, &image_rect, &pos_rect, 0, &center, SDL_FLIP_NONE);
        }
        item = item->next;
    }
}

void window_renderTransform(const Transform transform, const Size2D sprite_size, SDL_Texture *texture)
{
    SDL_Rect pos_rect;
    pos_rect.x = transform.position.x;
    pos_rect.y = transform.position.y;
    pos_rect.w = sprite_size.w * transform.scale;
    pos_rect.h = sprite_size.h * transform.scale;

    SDL_Rect image_rect;
    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.w = sprite_size.w;
    image_rect.h = sprite_size.h;

    SDL_Point center;
    center.x = sprite_size.w * transform.scale / 2;
    center.y = sprite_size.h * transform.scale / 2;

    SDL_SetTextureAlphaMod(texture, 255);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_RenderCopyEx(renderer, texture, &image_rect, &pos_rect, transform.angle, &center, SDL_FLIP_NONE);
}

void window_renderEx(const Vector2D position, const Size2D sprite_size, const Size2D target_size, double angle, Color color, SDL_Texture *texture)
{
    SDL_Rect pos_rect;
    pos_rect.x = position.x;
    pos_rect.y = position.y;
    pos_rect.w = target_size.w;
    pos_rect.h = target_size.h;

    SDL_Rect image_rect;
    image_rect.x = 0;
    image_rect.y = 0;
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

SDL_Texture * window_loadTexture(const char *path)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface!= NULL) 
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            fprintf(stderr, "[Engine] Unable to create texture from %s surface: %s\n", path, SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }
    else 
    {
        fprintf(stderr, "[Engine] Unable to load image %s : %s\n", path, IMG_GetError());
    }

    return texture;
}

void window_display()
{
    SDL_RenderPresent(renderer);
}

void * window_destroyTexture(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
    return NULL;
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

