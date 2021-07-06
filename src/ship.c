#include "ship.h"

void ship_init(Ship *ship, SDL_Texture *texture)
{
    ship->transform = (Transform) {(Vector2D) {0, 720 / 2}, 1, 0};
    ship->sprite = sprite_create(texture, 3, (Size2D) { 1024 / 4, 128 });
    ship->sprite.animations[0] = (Animation) { false, 1, 1, 0 };
    ship->sprite.animations[1] = (Animation) { false, 0, 1, 0 };
    ship->sprite.animations[2] = (Animation) { false, 2, 1, 0 };
    ship->collider = (BoxCollider) { (Vector2D) { 1024 / 8 + 20, 64 }, (Size2D) { (1024 / 4) - 120 , 60 }};
}

void ship_handleEvents(Ship *ship, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    ship->velocity.y = -1;
                    ship->sprite.current_animation = 1;
                    break;
                case SDLK_DOWN:
                    ship->velocity.y = 1;
                    ship->sprite.current_animation = 2;
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
                    ship->sprite.current_animation = 0;
                    break;
                case SDLK_DOWN:
                    if (ship->velocity.y > 0)
                        ship->velocity.y = 0;
                    ship->sprite.current_animation = 0;
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
    float new_y_pos = ship->transform.position.y + ship->velocity.y * SHIP_SPEED * delta_time;
    float new_x_pos = ship->transform.position.x + ship->velocity.x * SHIP_SPEED / ((ship->velocity.x < 0) ? 2 : 1) * delta_time;
    
    if (new_y_pos + ship->collider.center.y - ship->collider.size.h / 2 >= 0 && new_y_pos + ship->collider.center.y + ship->collider.size.h / 2 <= WINDOW_HEIGHT)
    {
        ship->transform.position.y = new_y_pos;
    }
    if (new_x_pos + ship->collider.center.x - ship->collider.size.w / 2 >= 0 && new_x_pos + ship->collider.center.x + ship->collider.size.w / 2 <= WINDOW_WIDTH)
    {
        ship->transform.position.x = new_x_pos;
    }
}

void ship_render(Ship *ship, SDL_Texture *texture)
{
    window_renderTransform(ship->transform, (Size2D) { 1024 / 4, 128 }, texture);
}