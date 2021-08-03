#include "engine/inputs.h"

static bool keys[NUMBER_OF_KEYDOWN_EVENTS];
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

void keyboard_handleEvents(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            keys[event->key.keysym.sym] = true;

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
                    break;
            }
            break;
        case SDL_KEYUP:
            keys[event->key.keysym.sym] = false;

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
                    break;
            }
            break;
        default:
            break;
    }
}

bool keyboard_getKey(int keycode)
{
    if (keycode >= 322 || keycode < 0)
    {
        fprintf(stderr, "[Engine] Keycode %d doesn't exist!\n", keycode);
        return 0;
    }

    return keys[keycode];
}

int keyboard_getAxisX()
{
    return axis_x;
}

int keyboard_getAxisY()
{
    return axis_y;
}