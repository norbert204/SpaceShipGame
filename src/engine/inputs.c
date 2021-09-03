#include "engine/inputs.h"

static u_int8_t *keys;
static int axis_x;
static int axis_y;

void keyboard_init()
{
    for (int i = 0; i < NUMBER_OF_KEYDOWN_EVENTS; i++)
    {
        keys[i] = false;
    }

    axis_x = 0;
    axis_y = 0;
}
/*
void keyboard_handleEvents(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    axis_y = -1;
                    break;
                case SDLK_DOWN:
                    axis_y = 1;
                    break;
                case SDLK_LEFT:
                    axis_x = -1;
                    break;
                case SDLK_RIGHT:
                    axis_x = 1;
                    break;
                default:
                    keys[event->key.keysym.sym] = true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    if (keys[SDLK_DOWN])
                        axis_y = 1;
                    else
                        axis_y = 0;
                    break;
                case SDLK_DOWN:
                    if (keys[SDLK_UP])
                        axis_y = -1;
                    else
                        axis_y = 0;
                    break;
                case SDLK_LEFT:
                    if (keys[SDLK_RIGHT])
                        axis_x = 1;
                    else
                        axis_x = 0;
                    break;
                case SDLK_RIGHT:
                    if (keys[SDLK_LEFT])
                        axis_x = -1;
                    else
                        axis_x = 0;
                    break;
                default:
                    keys[event->key.keysym.sym] = false;
                    break;
            }
            break;
        default:
            break;
    }
}*/

void keyboard_update()
{
    keys = SDL_GetKeyboardState(NULL);

    //  This needs some optimizing

    if (keys[SDL_SCANCODE_LEFT])
    {
        axis_x = -1;
    }
    else if (keys[SDL_SCANCODE_RIGHT])
    {
        axis_x = 1;
    }
    else
    {
        axis_x = 0;
    }

    if (keys[SDL_SCANCODE_UP])
    {
        axis_y = -1;
    }
    else if (keys[SDL_SCANCODE_DOWN])
    {
        axis_y = 1;
    }
    else
    {
        axis_y = 0;
    }
}

bool keyboard_getKey(int scancode)
{
    /*
    if (keycode >= 322 || keycode < 0)
    {
        fprintf(stderr, "[Engine] Keycode %d doesn't exist!\n", keycode);
        return 0;
    }
    */
    return keys[scancode];
}

int keyboard_getAxisX()
{
    return axis_x;
}

int keyboard_getAxisY()
{
    return axis_y;
}