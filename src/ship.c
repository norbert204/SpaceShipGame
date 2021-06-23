#include "ship.h"

void ship_init(Ship *ship)
{
    ship->transform = (Transform) {(Vector2D) {0, 720 / 2}, 1, 0};
    ship->collision = (BoxCollider) { (Vector2D) { 20, 0 }, (Size2D) { (1024 / 4) - 120 , 60 }};
}

void ship_handleEvent(Ship *ship, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    ship->velocity.y = -1;
                    break;
                case SDLK_DOWN:
                    ship->velocity.y = 1;
                    break;
                case SDLK_RIGHT:
                    ship->velocity.x = 1;
                    break;
                case SDLK_LEFT:
                    ship->velocity.x = -1;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    if (ship->velocity.y < 0)
                        ship->velocity.y = 0;
                    break;
                case SDLK_DOWN:
                    if (ship->velocity.y > 0)
                        ship->velocity.y = 0;
                    break;
                case SDLK_RIGHT:
                    if (ship->velocity.x > 0)
                        ship->velocity.x = 0;
                    break;
                case SDLK_LEFT:
                    if (ship->velocity.x < 0)
                        ship->velocity.x = 0;
                    break;
            }
            break;
    }
}

void ship_update(Ship *ship)
{
    float newYPos = ship->transform.position.y + ship->velocity.y * SHIP_SPEED * delta_time;
    float newXPos = ship->transform.position.x + ship->velocity.x * SHIP_SPEED / ((ship->velocity.x < 0) ? 2 : 1) * delta_time;
    
    //  TODO: ezt újraírni mert nem a legjobb a működése
    if (newYPos > 0 - ship->collision.size.h / 4 && newYPos < WINDOW_HEIGHT - 1.25f * ship->collision.size.h)
    {
        ship->transform.position.y = newYPos;
    }
    if (newXPos > 0 - ship->collision.size.w / 4 && newXPos < WINDOW_WIDTH - 1.25f * ship->collision.size.w)
    {
        ship->transform.position.x = newXPos;
    }
}