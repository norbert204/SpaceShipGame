#include "engine/textures.h"

static int tex_length = 0;
static int tex_capacity = 2;

Texture *loaded_textures = NULL;

void textures_load(const char *path, const char *name)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface != NULL) 
    {
        texture = SDL_CreateTextureFromSurface(window_getRenderer(), surface);
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

    if (loaded_textures == NULL) 
    {
        loaded_textures = malloc(tex_capacity * sizeof(Texture));
    }

    if (tex_length == tex_capacity)
    {
        tex_capacity *= 2;
        loaded_textures = realloc(loaded_textures, sizeof(Texture) * tex_capacity);
    }

    loaded_textures[tex_length] = (Texture) { name, texture };
    tex_length++;
}

SDL_Texture *textures_getTexture(char *name)
{
    for (int i = 0; i < tex_length; i++)
    {
        if (strcmp(loaded_textures[i].name, name) == 0)
        {
            return loaded_textures[i].texture;
        }
    }

    return NULL;
}

void textures_destroy()
{
    for (int i = 0; i < tex_length; i++)
    {
        SDL_DestroyTexture(loaded_textures[i].texture);
    }
    free(loaded_textures);
}